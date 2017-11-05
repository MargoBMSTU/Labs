#ifndef MYSTRING_
#define MYSTRING_

#include <iostream>
#include <cstring> // strlen, strcpy
#include <algorithm> //swap
#include <cctype>


#define STEP 100

class String { 
public:
	String(const char *str = "");
	String(const String &other);
	int len();
	int len() const ;
	
	String& operator = (const String &other);							
	String& operator += (const char c);
	String& operator += (const String &other);	
	char& operator [] (int i);
	char operator [] (int i) const ;
	friend std::ostream& operator << (std::ostream& os, String const& obj);
	friend std::istream& operator >> (std::istream& is, String& obj);
	friend bool operator == (const String s1, const String s2);
	friend bool operator < (const String s1, const String s2);
	~String();
	void append(const String &other);
	void append(const char c);

	void swap_s(String &other);
private:	
	int size;
	char *str;
};



String operator + (String s1, String const& s2);
String operator + (String s, const char c);
bool operator != (const String s1, const String s2);

bool operator > (const String s1, const String s2);
bool operator <= (const String s1, const String s2);
bool operator >= (const String s1, const String s2);




#endif 