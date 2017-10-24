#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
	char *p = NULL;
	p = (char*)malloc(10);
	strcpy(p, "0123456789");

	cin.get();
	cin.get();
	return 0;
}