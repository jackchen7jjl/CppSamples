#include "EventDispatcher.h"

void EventDispatcher::dispatch(Event *e)
{
	if(mCallBack != nullptr)
		mCallBack(e);
	if (mCb != nullptr)
	{
		//(mThisObj->a)(e);
		(mThisObj->*mCb)(e);
	}
}

void EventDispatcher::addEventListener(EventCallBackPtr callBack)
{
	mCallBack = callBack;
}

void EventDispatcher::addEventListener(ClassEventCallBackPtr callBack)
{
	mCb = callBack;
}

void EventDispatcher::addEventListener(ClassEventCallBackPtr callBack,Object *thisObj)
{
	mCb = callBack;
	mThisObj = thisObj;
}