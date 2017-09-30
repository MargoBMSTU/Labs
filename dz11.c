#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100 // максимальный размер слова 

static int state = 1; /*Переменная изменяющая своё значение, когда встречается символ новой строки*/

struct tnode { /* узел дерева */
	char *word; /* указатель на текст */
	int count; /* число вхождений */
	struct tnode *left; /* левый сын */
	struct tnode *right; /* правый сын */
	int n; /*Число абзацев, содержащих слово*/
	int st; /*Переменная для сравнения с внешней переменной state*/
}; 



/* talloc: создает tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}



/* addtree: добавляет узел со словом w в р или ниже него */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL){
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
		p->n = 1;
		p->st = 0;
	} 
	else if ((cond = strcmp(w, p->word)) == 0){
		p->count++; /* это слово уже встречалось */
		if (p->st != state){ 		/*если с последней встречи данного слова изменилось*/
			p->n++;								/*значение внешней переменной state(был переход на новую строку)*/
			p->st = state;				/*увеличиваем счетчик абзацев и сравниваем значение st=state*/
		}
	}
	else if (cond < 0) /* меньше корня левого поддерева */
		p->left = addtree(p->left, w);
	else /* больше корня правого поддерева */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: упорядоченная печать дерева р */
void treeprint(struct tnode *p, int num)
{
	if (p != NULL){
		treeprint(p->left, num);
		if (p->n >= num)
			printf("In paragraphs:%d   Number of occurrences:%d    Word:%s\n",p->n, p->count, p->word);
		treeprint(p->right, num);
	}
}

char buf[100]; /* буфер для ungetch */
static int bufp = 0; /* след, свободная позиция в буфере */

int getch(FILE * fp) /* взять (возможно возвращенный) символ */
{
	return (bufp > 0) ? buf[--bufp] : fgetc(fp);
}
void ungetch(char c)
{
	if (bufp >= MAXWORD)
		printf ("ungetch: слишком много символов\n");
	else
		buf[bufp++] = c;
}



char getword(char* word,int limit, FILE * fp){
	char c = 0;
	char *string = word;
	while(isspace(c = getch(fp)) || ispunct(c)){ /*пропускаем пробелы и ,;.:*/
		if (c == '\n')   /*если сивол c это перевод строки тогда */
			++state;			/*увеличиваем глобальную переменную*/
	}

	if (c != EOF)
		*string++ = c;
	if (!isalpha(c)) {
		*string = '\0';
		return c;
	}
	for ( ; --limit > 0; string++)
		if (!isalnum(*string = getch(fp))) {
			ungetch(*string);
			break;
	}
	*string = '\0';
	return word[0];
}

void treefree(struct tnode *p) /*Освобождение памяти*/
{
	if (p != NULL){
		if (p->left == NULL && p->right == NULL)
			free(p);
		else if (p->left != NULL)
			treefree(p->left);
		else if (p->right != NULL)
			treefree(p->right);
	}
}

int main (int argc, char *argv[]){
	char word[MAXWORD];
	struct tnode *root = NULL;
	FILE * fp;
	int n = 0;
	if (argc != 3){
		printf("wrong input.\n Usage: ./<name> <-N> <path> \nor\nUsage: ./<name> <path> <-N>");
		return 0;
	}
	if ( (**(argv+1))== '-'){
		n = atoi( *(argv + 1) + 1 );
		fp = fopen(argv[2], "r");
	}
	else if(**(argv+2) == '-'){
		n = atoi( *(argv + 2) + 1 );
		fp = fopen(argv[1], "r");
	}
	else {
		printf("wrong input.\n Usage: ./<name> <-N> <path> \nor\nUsage: ./<name> <path> <-N>");
		return 0;
	}
	while(getword(word, MAXWORD, fp) != EOF){
			root = addtree(root, word);
	}
	treeprint(root,n);
	treefree(root);
	fclose(fp);
	return 0;
}

