#pragma once
#include "Event.h"
#include "EventDispatcher.h"

class ClassA:public EventDispatcher
{
public:
	ClassA(char *name);
	void printText(char *s);
	void printImpl(Event *e);

private:
	char *mName;
};
