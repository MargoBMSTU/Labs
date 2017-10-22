#include <iostream>
#include <cstring>
#include <fstream>

#define MAXLEN 100
using namespace std;


void cpy (char* str1,const char* str2){
	for (; *str2 != '\0'; ++str2,++str1)
		*str1 = *str2;
	*str1 = '\0'; 
	return;
}

class product{
public:
	product(const char* s = "", const char* s2 = "", int pr = 0, int days = 0, int count = 0):
	 	name(new char[strlen(s)+1]),manufacturer(new char[strlen(s2)+1]), price(pr), days(days), amount(count)
		{
			cpy(this->name,s);
			cpy(this->manufacturer, s2);
		}

	product(const product& other){
		this->name = new char [strlen(other.name)+1];
		cpy(this->name, other.name);
		this->manufacturer = new char [strlen(other.manufacturer)+1];
		cpy(this->manufacturer, other.manufacturer);
		this->price = other.price;
		this->days = other.days;
		this->amount = other.amount;
	}	

	product& operator= (const product& other){
		delete [] this->name;
		this->name = new char [strlen(other.name)+1];
		cpy(this->name,other.name);
		delete [] this->manufacturer;
		this->manufacturer = new char [strlen(other.manufacturer)+1];
		cpy(this->manufacturer,other.manufacturer);
		this->price = other.price;
		this->days = other.days;
		this->amount = other.amount;
		return *this;
	}

	void set_name (const char* s){	
		delete [] this->name;
		this->name = new char[strlen(s)+1];
		cpy(this->name, s);
		return;
	}
	void set_manufacturer (const char* s){	
		delete [] this->manufacturer;
		this->manufacturer = new char[strlen(s)+1];
		cpy(this->manufacturer, s);
		return;
	}
	void set_price (int pr){	
		this->price = pr;
		return;
	}
	void set_days (int d){	
		this->days = d;
		return;
	}
	void set_amount (int c){	
		this->amount =c;
		return;
	}

	char* get_name(){
		return this->name;
	}
	char* get_manufacturer(){
		return this->manufacturer;
	}
	int get_price(){
		return this->price;
	}
	int get_days(){
		return this->days;
	}
	int get_amount(){
		return this->amount;
	}

	void show_name(){
		cout << "Name: " << this->name << endl;
		return;
	}
	void show_manufacturer(){
		cout << "manufacturer: " << this->manufacturer << endl;
		return;
	}
	void show_price(){
		cout << "price: " << this->price << endl;
		return;
	}
	void show_days(){
		cout << "days: " << this->days << endl;
		return;
	}
	void show_amount(){
		cout << "amount: " << this->amount << endl;
		return;
	}

	void show_all(){
		cout << name <<" "<< manufacturer <<" "<< price <<" "<< days <<" "<< amount << endl;
	}	

	~product(){
		delete [] this->name;
		delete [] this->manufacturer;
	}
private:
	char* name;
	char* manufacturer;
	int price;
	int days;
	int amount;
};	

class list;

class element{
friend list;
private:
	product* data;
	element* next;
};

class list{
public:
	friend element;
	list(): head(NULL){}
	~list(){
		while (head != NULL){
			element* tmp = head->next;
			delete head;
			head = tmp;
		}
	}
	void add(product& elem){
		element* tmp = new element;
		tmp->data = new product(elem);
		tmp->next = head;
		head = tmp;
	}
	void show(){
		element* tmp = head;
		while (tmp != 0){
			tmp->data->show_all();
			tmp = tmp->next;
		}
	}
private:
	element* head;
};

void create_el(product& p,const char* s,const char* s2,int pr,int d,int am){
	p.set_name(s);
	p.set_manufacturer(s2);
	p.set_price(pr);
	p.set_days(d);
	p.set_amount(am);
}

void inputElem(product &p){
	char name[MAXLEN];
	char manufacturer[MAXLEN];
	int price = -1;
	int days = -1;
	int amount = -1;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter manufacturer: ";
	cin >> manufacturer; 
	cout << "Enter price: ";
	cin >> price;
	cout << "Enter days: ";
	cin >> days;
	cout << "Enter amount: ";
	cin >> amount;
	create_el(p, name, manufacturer, price, days, amount);
	return;
}

void firstlist (product *mas,int size, list& l,const char *given_name){
	for (int i = 0; i < size; ++i) {
		if (strcmp(mas[i].get_name(),given_name) == 0)
			l.add(mas[i]);
	}	
	return;
}

void secondlist (product *mas,int size, list& l,const char *given_name,int given_price){
	for (int i = 0; i < size; ++i) {
		if (strcmp(mas[i].get_name(),given_name) == 0)
			if(mas[i].get_price() <= given_price)
				l.add(mas[i]);
	}
	return;
}

void thirdlist (product *mas,int size, list& l,int given_days){
	for (int i = 0; i < size; ++i) {
		if (mas[i].get_days() >= given_days)
			l.add(mas[i]);
	}	
	return;
}


int main (int argc, char *argv[]){
	int size;
	cout << "Enter mass size: ";
	cin >> size;
	product* mas = new product[size];
	for (int i = 0; i < size; ++i){
		cout << i << " element:"<< endl;
		inputElem(mas[i]);
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < size; ++i) 
		mas[i].show_all(); 
	cout << endl;
	char given_name[MAXLEN];
	int given_price;
	int given_days;
	cout << "enter give_name: ";
	cin >> given_name;
	cout << "enter given_price: ";
	cin >> given_price;
	cout << "enter given_days: ";
	cin >> given_days;
	cout << endl;
	list l1;
	list l2;
	list l3;
	firstlist(mas,size,l1,given_name);
	secondlist(mas,size,l2,given_name,given_price);
	thirdlist(mas,size,l3,given_days);
	cout << "first list: ";
	l1.show();
	cout << "second list: ";
	l2.show();
	cout << "third list: ";
	l3.show();
	delete [] mas;
	return 0;
}