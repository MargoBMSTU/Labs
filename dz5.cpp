#include <iostream>
#include <cstring> // strlen, strcpy
#include <algorithm> //swap
#include <cctype>
#include <string>

#define STEP 100
using namespace std;

class String {
public:
	String(const char *str = "") {
		this->size = strlen(str);
		this->str = new char[size+1];
		strcpy(this->str,str);
	}
	String(const String &other){ 
		this->size = other.size;
		this->str = new char[size+1];
		strcpy(this->str,other.str);
	}
	int len(){
		return this->size;
	}
	int len() const {  
		return this->size; 
	}
	
	String& operator = (const String &other) {  
		if (this != &other)				
			String(other).swap_s(*this); 
		return *this;                   
	}									
	String& operator += (const char c){
		this->append(c);				
		return *this;					
	}
	String& operator += (const String &other){ 
		this->append(other);				  
		return *this;						
	}										 
	char& operator [] (int i){	
		if (i <= this->size)
			return str[i];
		else
			return str[this->size];
	}
	char operator [] (int i) const { 
		if (i <= this->size)		
			return str[i];			
		else
			return '\0';
	}
	friend std::ostream& operator << (std::ostream& os, String const& obj){ 
		return os << obj.str;
	}
	friend std::istream& operator >> (std::istream& is, String& obj){
		is.sync(); 
		while(isspace(is.peek())) 
			is.get();			
		int cap = STEP; 
		char* tmp = new char[cap+1];
		int i = 0;
		while ( !isspace(is.peek()) ){ 
			if (i < cap)
				is >> tmp[i++];
			else { 
				cap = cap + STEP;
				char *temp = new char[cap+1];
				for (int j = 0; j < i; ++j) 
					temp[j] = tmp[j]; 
				delete [] tmp; 
				tmp = temp; 
				is >> tmp[i++];
			}
			tmp[i] = '\0'; 
		}
		delete [] obj.str;
		obj.size = strlen(tmp);
		obj.str = new char[obj.size+1]; 
		strcpy(obj.str,tmp);
		delete [] tmp;
		return is;
	}
	friend bool operator == (const String s1, const String s2){
		if (strcmp(s1.str,s2.str)==0)							
			return true;										
		else 													
			return false;
	}
	friend bool operator < (const String s1, const String s2){
		if (strcmp(s1.str,s2.str) < 0)
			return true;
		else 
			return false;
	}
	~String(){  
		delete [] str;
	}
	void append(const String &other){  
		char *p = new char[size + other.size + 1];
		strcpy(p,this->str);
		int i = this->size;
		for (int k = 0; i < (this->size + other.size) && k < other.size; ++i,++k) 
			p[i] = other.str[k];
		p[i] = '\0';
		delete [] (this->str);
		this->str = p;
		this->size = strlen(str);
	}
	void append(const char c){  
		char *tmp = new char[size+2];
		strcpy(tmp, str);
		tmp[this->size] = c;
		tmp[this->size + 1] = '\0';
		delete [] str;
		this->str = tmp;
		this->size = strlen(str);
	}

	void swap_s(String &other){ 
		swap(size,other.size);
		swap(str, other.str);
	}
private:	
	int size;
	char *str;
};



String operator + (String s1, String const& s2){ 
	return s1 += s2;							
}
String operator + (String s, const char c){
	return s += c;							
}
bool operator != (const String s1, const String s2){
	return !(s1 == s2);
}

bool operator > (const String s1, const String s2){
	return s2 < s1;
}
bool operator <= (const String s1, const String s2){
	return !(s2 < s1);
}
bool operator >= (const String s1, const String s2){
	return !(s1 < s2);
}



void bubblesort(String* m, int size){ 
	for (int i = 0; i < size; ++i) 
		for (int j = i; j < size; ++j) 
			if (m[j] < m[i])
				m[j].swap_s(m[i]);
}

void printMas(String* m, int size){ 
	for (int i = 0; i < size; ++i) {
		cout << m[i] << " ";
	}
	cout << endl;
}

int main (int argc, char *argv[]){
	cout << "Enter mas size:";
	int size = 0;
	cin >> size; 
	cout << "Enter " << size << " words" << endl;
	String* mas = new String[size];
	for (int i = 0; i < size; ++i) {
		cin >> mas[i];
	}
	cout << "Your input:" <<endl;
	printMas(mas,size);
	bubblesort(mas,size);
	cout << "After sort:" <<endl;
	printMas(mas,size);
	delete	[] mas;
	return 0;
}
