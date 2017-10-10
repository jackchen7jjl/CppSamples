#include <iostream>
#include "ClassA.h"
#include "EventDispatcher.h"
#include "Event.h"

using namespace std;

typedef void(*FP)(char *s);

void f1(char* s) { cout << "f1 " << s << endl; }
void f2(char* s) { cout << "f2 "<< s << endl; }
void f3(char* s) { cout << "f3 "<< s << endl; }

//定义带参回调函数
void PrintfText(char* s)
{
	printf(s);
}

//定义实现带参回调函数的"调用函数"
void CallPrintfText(FP fp, char* s)
{
	fp(s);
}

typedef void (ClassA::*FP2)(char *);

void onComplete(Event *e)
{
	cout <<" onComplete " << e->getType() << endl;
}

int main()
{
	//void* a[] = { f1,f2,f3 };   //定义了指针数组，这里a是一个普通指针
	//a[0]("Hello World!\n"); //编译错误，指针数组不能用下标的方式来调用函数

	FP f[] = { f1,f2,f3 };      //定义一个函数指针的数组，这里的f是一个函数指针
	f[0]("Hello World!"); //正确，函数指针的数组进行下标操作可以进行函数的间接调用

	CallPrintfText(f[2],"hello call back!");

	ClassA clsA("clsA");
	clsA.printText("hello!");

	ClassA clsB("clsB");

	FP2 fpA = (FP2)&ClassA::printText;
	(clsB.*fpA)("oooo");

	ClassA *clsAP = &clsA;
	(clsAP->*fpA)("hhh");

	EventDispatcher ed1;
	ed1.addEventListener(onComplete);
	ed1.addEventListener((ClassEventCallBackPtr)&ClassA::printImpl,clsAP);
	ed1.dispatch(new Event(122));

	

	cin.get();
	cin.get();
	return 0;
}

void Invoke(char* s)
{ 
	cout << s << endl;
}