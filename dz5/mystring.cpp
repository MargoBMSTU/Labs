#include "mystring.hpp"



String::String(const char *str) {     
	this->size = strlen(str);
	this->str = new char[size+1];
	strcpy(this->str,str);
}


String::String(const String &other){   
	this->size = other.size;
	this->str = new char[size+1];
	strcpy(this->str,other.str);
}


int String::len(){
	return this->size;
}


int String::len() const {    
	return this->size; 
}


String& String::operator = (const String &other) {  
	if (this != &other)				
		String(other).swap_s(*this); 
	return *this;                    
}


String& String::operator += (const char c){ 
	this->append(c);				
	return *this;				
}


String& String::operator += (const String &other){ 
	this->append(other);
	return *this;
}


char& String::operator [] (int i){
	if (i <= this->size)
		return str[i];
	else
		return str[this->size];
}


char String::operator [] (int i) const {
	if (i <= this->size)
		return str[i];
	else
		return '\0';
}


std::ostream& operator << (std::ostream& os, String const& obj){
	return os << obj.str;
}


std::istream& operator >> (std::istream& is, String& obj){
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


bool operator == (const String s1, const String s2){
	if (strcmp(s1.str,s2.str)==0)
		return true;
	else
		return false;
}


bool operator < (const String s1, const String s2){
	if (strcmp(s1.str,s2.str) < 0)
		return true;
	else 
		return false;
}


String::~String(){
	delete [] str;
}


void String::append(const String &other){
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


void String::append(const char c){
	char *tmp = new char[size+2];
	strcpy(tmp, str);
	tmp[this->size] = c;
	tmp[this->size + 1] = '\0';
	delete [] str;
	this->str = tmp;
	this->size = strlen(str);
}


void String::swap_s(String &other){
	std::swap(size,other.size);
	std::swap(str, other.str);
}




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