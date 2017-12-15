#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <windows.h>

using namespace std;

volatile int counter(0); // non-atomic counter
std::mutex mtx;           // locks access to counter

std::mutex mtx1;

void attempt_10k_increases(int index) 
{

	for (int i = 0; i<10; ++i) 
	{
		if (index < 5)
		{
			if (mtx.try_lock())
			{   // only increase if currently not locked:
				++counter;
				Sleep(15);
				mtx.unlock();
				cout << index << endl;
			}
		}
		else
		{
			if (mtx1.try_lock())
			{   // only increase if currently not locked:
				++counter;
				Sleep(15);
				mtx1.unlock();
				cout << index << endl;
			}
		}

	}
}

int main2(int argc, const char* argv[]) {
	std::thread threads[10];
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(attempt_10k_increases,i);

	for (auto& th : threads) th.join();
	std::cout << counter << " successful increases of the counter.\n";

	std::cin.get();
	std::cin.get();
	return 0;
}