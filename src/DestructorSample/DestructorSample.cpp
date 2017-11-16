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
	
	//virtual ~Animal()
	//{
	//	std::cout << "delete Animal " << _name << "__" << _id << std::endl;
	//}
	
	virtual void Eat() = 0;

	virtual void Run()
	{
		std::cout << "Animal " << _name << "__"  << " Run " << std::endl;
	}

	Animal& operator=(const Animal &animal) = delete;
	//{
	//	_id = animal._id;	
	//	std::cout << "Animal operate =  " << _name << std::endl;
	//	return *this;
	//}

protected:
	int _id;
	char *_name;
	static int UID;
};

int Animal::UID = 1;

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

	void Run() override
	{
		std::cout << "Cat " << _name << "__"  << _id << " Run " << std::endl;
	}

	//Cat& operator=(const Cat &animal)
	//{
	//	_id = animal._id + 10;
	//	std::cout << "Cat operate =  " << _name << std::endl;
	//	return *this;
	//}
};

int main()
{
	Animal *cat = new Cat("Tom");
	cat->Eat();
	cat->Run();
	

	Cat *cat1 = new Cat("Lily");
	cat1->Eat();
	cat1->Run();

	Cat *cat2 = new Cat("lucy");
	//*cat2 = *cat1;
	cat2->Run();

	delete cat;
	delete cat1;
	delete cat2;

	std::cin.get();
	std::cin.get();
	return 0;
}