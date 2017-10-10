#pragma once
#include "Student.h"
#include <memory>

class Teacher
{
public:
	Teacher(string name, StudentSP stu) :m_name(name), m_stu(stu)
	{
		std::cout << "create teacher " << name << " -- " << stu->getName() << std::endl;
	}
	~Teacher() { std::cout << "release teacher " << m_name << std::endl; }
private:
	StudentSP m_stu;
	string m_name;
};
