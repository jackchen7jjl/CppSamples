#pragma once
#include <iostream>

class Object
{

};

class Event:public Object
{
public:
	Event(int type) :mType(type) {};
	int getType()
	{
		return mType;
	}
private:
	int mType;
};

class EventA :public Event
{
public:
	EventA(int type) :Event(type) {};
};
