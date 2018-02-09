#include <iostream>
#include <stdarg.h>

using namespace std;

void mprint(const char* format,...)
{
	va_list vl;
	va_start(format, vl);

}

int main()
{	
	int a = 6;
	double b = 8.9;
	float c = 0.5f;
	char *d = "hello";

	mprint("a=b",a,b,c,d);

	std::cin.get();
	std::cin.get();
	return 0;
}