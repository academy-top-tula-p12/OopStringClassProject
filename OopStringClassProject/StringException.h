#pragma once
#include "String.h"

class StringException
{
	String message;
public:
	StringException(String message) 
		: message{ message } {};

	String Message() { return message; }
};

