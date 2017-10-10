#include <iostream>

using namespace std;

int main(int agc, wchar_t *argv[], wchar_t *envp[])
{
	for (int i = 0; i < agc; i++)
	{
		cout << argv[i] << "::" << envp[i] << endl;
	}

	cin.get();
	cin.get();
	return 0;
}