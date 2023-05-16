#include <string.h>
#include "String.h"
#include "StringException.h"


String::String() : length{ 0 }, cstr{ nullptr } {}

String::String(const char cstr[])
{
	this->length = strlen(cstr);
	this->cstr = new char[this->length + 1];
	strcpy_s(this->cstr, this->length + 1, cstr);
}

String::String(char symbol, int count)
{
	this->length = count;
	this->cstr = new char[this->length + 1];

	for (int i = 0; i < count; i++)
		this->cstr[i] = symbol;
	this->cstr[count] = '\0';
}

String::String(const String& s)
{
	this->length = s.length;
	this->cstr = new char[this->length + 1];

	strcpy_s(this->cstr, this->length + 1, s.cstr);
}

String::String(String&& s) noexcept
{
	this->length = s.length;
	this->cstr = s.cstr;

	s.cstr = nullptr;
}

String::~String()
{
	if (this->cstr)
		delete[] this->cstr;
}

int String::Length()
{
	return length;
}

String& String::operator=(const String& s)
{
	if (&s == this)
		return *this;

	delete[] this->cstr;
	
	this->length = s.length;
	this->cstr = new char[this->length + 1];

	strcpy_s(this->cstr, this->length + 1, s.cstr);

	return *this;
}

String& String::operator=(String&& s) noexcept
{
	if (&s == this)
		return *this;

	delete[] this->cstr;

	this->length = s.length;
	this->cstr = s.cstr;

	s.cstr = nullptr;

	return *this;
}

String& String::operator=(const char cstr[])
{
	delete[] this->cstr;

	this->length = strlen(cstr);
	this->cstr = new char[this->length + 1];
	strcpy_s(this->cstr, this->length + 1, cstr);

	return *this;
}

String& String::operator=(char symbol)
{
	delete[] this->cstr;

	this->length = 1;
	this->cstr = new char[2];
	this->cstr[0] = symbol;
	this->cstr[1] = '\0';

	return *this;
}

char& String::operator[](int index)
{
	return cstr[index];
}

bool String::IsEmpty()
{
	return this->length == 0;
}

void String::Clear()
{
	delete[] this->cstr;
	this->cstr = nullptr;
	this->length = 0;
}

bool String::Erase(int position, int count)
{
	if (position < 0 || position > this->length)
		return false;
	if (count < 1 || count > this->length - position)
		return false;

	char* cstrNew = new char[this->length - count + 1];
	for (int i = 0; i < position; i++)
		cstrNew[i] = this->cstr[i];
	int indexNew = position;
	for (int i = position + count; i < this->length; i++)
		cstrNew[indexNew++] = this->cstr[i];
	cstrNew[indexNew] = '\0';
	
	this->length -= count;
	delete[] this->cstr;
	this->cstr = cstrNew;

	return true;
}

String& String::Insert(String s, int position)
{
	char* cstrNew = new char[this->length + s.length + 1];
	int indexNew{};
	for (int i = 0; i < position; i++)
		cstrNew[indexNew++] = this->cstr[i];
	for(int i = 0; i < s.length; i++)
		cstrNew[indexNew++] = s.cstr[i];
	for (int i = position; i < this->length; i++)
		cstrNew[indexNew++] = this->cstr[i];
	cstrNew[indexNew] = '\0';

	delete[] this->cstr;
	this->cstr = cstrNew;
	this->length += s.length;

	return *this;
}

String& String::Insert(char cstr[], int position)
{
	return this->Insert(String(cstr), position);
}

String& String::Insert(char symbol, int position)
{
	String s;
	s = symbol;
	return this->Insert(s, position);
}

String& String::Append(String s)
{
	char* cstrNew = new char[this->length + s.length + 1];
	int indexNew{};

	for (int i = 0; i < this->length; i++)
		cstrNew[indexNew++] = this->cstr[i];
	for (int i = 0; i < s.length; i++)
		cstrNew[indexNew++] = s.cstr[i];

	cstrNew[indexNew] = '\0';

	delete[] this->cstr;
	this->cstr = cstrNew;
	this->length += s.length;
}

String& String::Append(char cstr[])
{
	return this->Append(String(cstr));
}

String& String::Append(char symbol)
{
	String s;
	s = symbol;
	return this->Append(s);
}

String& String::operator+=(String s)
{
	return this->Append(s);
}

String& String::operator+=(char cstr[])
{
	return this->Append(cstr);
}

String& String::operator+=(char symbol)
{
	return this->Append(symbol);
}

String String::operator+(String s)
{
	String strNew(*this);
	strNew.Append(s);
	return strNew;
}

String String::operator+(char cstr[])
{
	return *this + String(cstr);
}

String String::operator+(char symbol)
{
	String s;
	s = symbol;
	return *this + s;
}

String String::SubString(int position, int count)
{
	if (position < 0 || position > this->length)
		throw new StringException("Invalid of position");
	if (count < 1 || count > this->length - position)
		throw new StringException("Invalid of count");
	
	char* cstrNew = new char[count];
	for (int i = 0; i < count; i++)
		cstrNew[i] = this->cstr[position + i];

	return String(cstrNew);
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
	out << s.cstr;
	return out;
}
