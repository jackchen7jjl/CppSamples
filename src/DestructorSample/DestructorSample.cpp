#include <iostream>

class Animal
{
public:
	Animal(char *name):_name(name)
	{
		_id = UID;
		UID++;
		std::cout << "New Animal "  << _name << "__" << _id << std::endl;
	}
	
	virtual ~Animal()
	{
		std::cout << "delete Animal " << _name << "__" << _id << std::endl;
	}
	
	virtual void Eat() = 0;

protected:
	int _id;
	char *_name;
	static int UID;
};

int Animal::UID = 0;

class Cat :public Animal
{
public:
	Cat(char *name):Animal(name) 
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
};

int main()
{
	Animal *cat = new Cat("Tom");
	cat->Eat();
	delete cat;

	Cat *cat1 = new Cat("Lily");
	delete cat1;

	std::cin.get();
	std::cin.get();
	return 0;
}