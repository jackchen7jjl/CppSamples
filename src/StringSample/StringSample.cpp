#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void toupperCase(string url)
{
	transform(url.begin(), url.end(), url.begin(), ::toupper);
	cout << url << endl;
}

int main()
{	
	string url0 = "Test/Grass.Bmp";
	toupperCase(url0);
	cout << url0 << endl;

	string url = url0;
	cout << url << endl;

	transform(url.begin(), url.end(), url.begin(), ::toupper);
	cout << url << endl;

	transform(url.begin(), url.end(), url.begin(), ::tolower);
	cout << url << endl;

	string bmpExtension = ".bmp0";

	size_t index = url.find(bmpExtension);
	cout << index << endl;

	if (index != url.npos)
	{
		cout << "Found!" << endl;
	}

	std::cin.get();
	std::cin.get();
	return 0;
}