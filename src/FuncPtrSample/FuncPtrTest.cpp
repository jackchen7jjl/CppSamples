#include <iostream>
#include "ClassA.h"
#include "EventDispatcher.h"
#include "Event.h"

using namespace std;

typedef void(*FP)(char *s);

void f1(char* s) { cout << "f1 " << s << endl; }
void f2(char* s) { cout << "f2 "<< s << endl; }
void f3(char* s) { cout << "f3 "<< s << endl; }

//������λص�����
void PrintfText(char* s)
{
	printf(s);
}

//����ʵ�ִ��λص�������"���ú���"
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
	//void* a[] = { f1,f2,f3 };   //������ָ�����飬����a��һ����ָͨ��
	//a[0]("Hello World!\n"); //�������ָ�����鲻�����±�ķ�ʽ�����ú���

	FP f[] = { f1,f2,f3 };      //����һ������ָ������飬�����f��һ������ָ��
	f[0]("Hello World!"); //��ȷ������ָ�����������±�������Խ��к����ļ�ӵ���

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