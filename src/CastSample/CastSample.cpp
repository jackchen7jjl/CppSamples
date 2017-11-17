#include <iostream>
#include <unordered_map>
#include <string>
#include <map>

using namespace std;

class Animal
{
public:
	Animal(string name,int id):_name(name)
	{
		_id = id;
		std::cout << "New Animal "  << _name << "__" << _id << std::endl;
	}
	
	virtual ~Animal()
	{
		std::cout << "delete Animal " << _name << "__" << _id << std::endl;
	}
	
	virtual void Eat() = 0;

	virtual void Run()
	{
		std::cout << "Animal " << _name << "__"  << " Run " << std::endl;
	}

protected:
	int _id;
	string _name;
};

class Cat :public Animal
{
public:
	Cat(string name, int id):Animal(name,id)
	{
		std::cout << "new Cat " << _name <<  std::endl;
	};

	~Cat() 
	{ 
		std::cout << "delete Cat " << _name << std::endl;
	};

	void Eat()
	{
		std::cout << "Cat Eat" << std::endl;
	}

	void Run() override
	{
		std::cout << "Cat " << _name << "__"  << _id << " Run " << std::endl;
	}
};

int main()
{	
	Cat a("lily",1);

	char *chars = new char[8]{65,67,3,4,70,71,72,73 };
	
	std::cout << chars[0] << chars[1] << std::endl;
	
	std::cout << &chars << endl;

	std::cout << chars << endl;

	short sh0 = *((short*)(chars));

	short sh1 = *(reinterpret_cast<short*>(chars));

	std::cout << sh0 <<  ", " << sh1 << std::endl;

	std::cin.get();
	std::cin.get();
	return 0;
}