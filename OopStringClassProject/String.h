#pragma once
#include <iostream>
class String
{
	char* cstr;
	int length;
public:
	String();
	String(const char cstr[]);
	String(char symbol, int count);
	String(const String& s);
	String(String&& s) noexcept;
	~String();

	int Length();

	String& operator=(const String& s);
	String& operator=(String&& s) noexcept;
	String& operator=(const char cstr[]);
	String& operator=(char symbol);

	char& operator[](int index);

	bool IsEmpty();
	void Clear();
	bool Erase(int position, int count);

	String& Insert(String s, int position);
	String& Insert(char cstr[], int position);
	String& Insert(char symbol, int position);

	String& Append(String s);
	String& Append(char cstr[]);
	String& Append(char symbol);

	String& operator+=(String s);
	String& operator+=(char cstr[]);
	String& operator+=(char symbol);

	String operator+(String s);
	String operator+(char cstr[]);
	String operator+(char symbol);

	String SubString(int position, int count);

	friend std::ostream& operator<<(std::ostream& out, const String& s);
};

