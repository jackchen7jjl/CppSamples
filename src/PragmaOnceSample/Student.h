#pragma once
#include <iostream>
#include <memory>
#include "Common.h"

class Student
{
public:
	Student(String name, int grade) :m_name(name), m_grade(grade) { std::cout << "create student " << m_name << std::endl; };
	~Student() { std::cout << "release student " << m_name << std::endl; }

	String getName() { return m_name; }

	String ToString();

private:
	String m_name;
	int m_grade;
	bool _isBoy;
};

typedef std::shared_ptr<Student> StudentSP;