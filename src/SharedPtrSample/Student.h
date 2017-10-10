#pragma once
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Student
{
public:
	Student(string name, int grade) :m_name(name), m_grade(grade) { cout << "create student " << m_name << endl; };
	~Student() { cout << "release student " << m_name << endl; }

	string getName() { return m_name; }

private:
	string m_name;
	int m_grade;
};

typedef shared_ptr<Student> StudentSP; 