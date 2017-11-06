#include "Common.h"

String operator+(String s, bool b)
{
	if (b)
		return s + "true";
	else
		return s + "false";
}