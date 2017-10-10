#pragma once
#include "Event.h"

typedef void(*EventCallBackPtr)(Event *);
typedef void(Object::*ClassEventCallBackPtr)(Event *);


class EventDispatcher:public Object
{
public:
	void dispatch(Event *e);
	void addEventListener(EventCallBackPtr callBack);
	void addEventListener(ClassEventCallBackPtr callBack);
	void addEventListener(ClassEventCallBackPtr callBack, Object *thisObj);
private:
	EventCallBackPtr mCallBack = nullptr;
	ClassEventCallBackPtr mCb = nullptr;
	Object *mThisObj = nullptr;
};