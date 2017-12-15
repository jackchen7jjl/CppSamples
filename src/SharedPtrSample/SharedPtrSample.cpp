#include <iostream>
#include <string>
#include "Student.h"
#include "Teacher.h"

using namespace std;

void foo(string name, std::shared_ptr<Student> s)
{
	Teacher t(name,s);
}

int main()
{
	{
		//StudentSP s = std::make_shared<Student>("jack", 9);
		//foo("t1",s);
		//foo("t2",s);

		Student *sp = new Student("jack2",2);
		std::shared_ptr<Student> ssp = std::shared_ptr<Student>(sp);
		//foo("t3", s2);
		//foo("t4", s2);
	}

	cin.get();
	cin.get();
	return 0;
}