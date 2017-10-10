#include "ClassA.h"
#include <iostream>

ClassA::ClassA(char *name)
{
	mName = name;
}

void ClassA::printImpl(Event *e)
{
	std::cout << mName  << " printImpl: " << e->getType() << std::endl;
}

void ClassA::printText(char *s)
{
	std::cout << mName << " printText text: " << s << std::endl;
}