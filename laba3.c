#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DELLTREE(A) free((A)->word);free(A) //макрос для полного удаления элемента дерева(строки и самого указателя)

struct tnode { 
	char *word; 
	struct tnode *left; 
	struct tnode *right;
	};

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *p, char *w)  //добавляет слово в дерево (+)
{	
	int cond;

	if (p == NULL){ 
		p = talloc(); 
		p->word = strdup(w); 
		p->left = p->right = NULL; 
		
	} 
	else if ((cond = strcmp(w, p->word)) == 0){ 
		return p; 
	}
	else if (cond < 0) { 
		p->left = addtree(p->left, w);
		}
	else 
		p->right = addtree(p->right, w);
	return p;
}

struct tnode* treeprint(struct tnode *p, char *w) //проверяет есть ли слово в дереве (?)
{
	int cond=0;
	if (p == NULL)
		printf("%s NO\n", w);
	else if((cond=strcmp(w,p->word)) == 0)
		printf("%s YES\n", w);
	else if (cond < 0)
		p->left = treeprint(p->left,w);
	else 
		p->right = treeprint(p->right,w);	
	return p;
}

struct tnode *removetree(struct tnode *p, char *w) //удаляет слово из дерева (-)
{
	int cond;
	if (p == NULL){ 
		return p;
	}  
	if ((cond = strcmp(w, p->word)) == 0){
		if (p->left && p->right) { 
			if (p->right->left == NULL)	{ 
				free(p->word); 
				p->word =strdup(p->right->word);  
				struct tnode* tmp = p->right;  
				p->right = p->right->right; 
				free(tmp); 
			}else {
				free(p->word); 
				p -> word = strdup(p -> right -> left -> word);
				p->right->left = removetree(p ->right ->left,p ->right -> left -> word);
			}
		}	
	
		else if (p->left){
			struct tnode* tmp2 = (p->left); 
			DELLTREE(p); 
			return tmp2; 
		}else if(p->right){
			struct tnode* tmp3 = p->right;
			DELLTREE(p);
			return tmp3;
		}else {
			DELLTREE(p); 
			return NULL; 
		}
	}		
	else if (cond < 0) 
		p->left = removetree(p->left, w);
	else
		p->right = removetree(p->right, w);
	return p;	
}

void treefree(struct tnode *p) 
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

int main(int argc, char *argv[]){
	if (argc != 2){
		printf("You must input 1 file path\n");
		return 1;
	}
	const char* file_name = *++argv;
	char s[30];
	FILE *f;
	f = fopen(file_name,"r");
	if (errno != 0){							
			printf("%s:%s\n",file_name, strerror(errno)); 
			return errno;  
	}
	struct tnode* root = NULL;
	while(fscanf(f,"%s", s) != EOF){
		if (s[0] =='+')
			root = addtree(root,s+1);
		else if (s[0] == '?')
			root = treeprint(root,s+1);
		else if (s[0] == '-')
			root = removetree(root, s+1);
		else {
			printf("Wrong file format. First letter in word must be +,- or ?\n");
			treefree(root);
			return 2;
		}
	}
	treefree(root);
	fclose(f);
	return 0;
}		