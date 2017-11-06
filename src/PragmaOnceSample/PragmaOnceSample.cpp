#include "Student.h"

int main(int argc, const char* argv[]) {
	Student s("jack",10);

	std::cout << s.ToString() << std::endl;

	std::cin.get();
	std::cin.get();
	return 0;
}