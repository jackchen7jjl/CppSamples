#include <iostream>
#include <unordered_map>
#include <string>
#include <map>

using namespace std;

class VirtulCls
{
public:
	virtual void Foo() = 0;
};

class Pet
{
public:
	Pet(string masterName):_masterName(masterName)
	{
		cout << "New Pet " << _masterName << endl;
	}

	~Pet()
	{
		cout << "Delete Pet " << _masterName << endl;
	}

	virtual void Play()
	{
		cout << "Pet Play " << _masterName << endl;
	}

protected:
	string _masterName;
};

class Animal
{
public:
	Animal(string name, int id) :_name(name)
	{
		_id = id;
		std::cout << "New Animal " << _name << "__" << _id << std::endl;
	}

	virtual ~Animal()
	{
		std::cout << "Delete Animal " << _name << "__" << _id << std::endl;
	}

	virtual void Eat()
	{
		std::cout << "Animal Eat" << _name << "__" << _id << std::endl;
	}

	virtual void Run()
	{
		std::cout << "Animal " << _name << "__" << " Run " << std::endl;
	}

protected:
	int _id;
	string _name;
};

class Cat :public Animal, public Pet, public VirtulCls
{
public:
	Cat(string name, int id,string masterName) :Animal(name, id), Pet(masterName), VirtulCls()
	{
		std::cout << "New Cat " << _name << "_" << _id << "_" << _masterName << std::endl;
	};

	~Cat()
	{
		std::cout << "Delete Cat " << _name << "_" << _id << "_" << _masterName << std::endl;
	};

	void Eat()
	{
		std::cout << "Cat Eat " << _name << "_" << _id << "_" << _masterName << std::endl;
	}

	void Run() override
	{
		std::cout << "Cat Run " << _name << "_" << _id << "_" << _masterName << std::endl;
	}

	void Foo() override
	{
		std::cout << "Cat Foo " << _name << "_" << _id << "_" << _masterName << std::endl;
	}
};

class Lion :public Animal
{
public:
	Lion(string name, int id,bool king):Animal(name, id),_king(king)
	{
		std::cout << "New Lion " << _name << "_" << _id << "_" << _king << std::endl;
	}

	~Lion()
	{
		std::cout << "Delete Lion " << _name << "_" << _id << "_" << _king << std::endl;
	}

	void Eat()
	{
		std::cout << "Lion Eat " << _name << "_" << _id << "_" << _king << std::endl;
	}

private:
	bool _king;
};

class BossCat :public Cat
{
public:
	BossCat(string name, int id, string masterName) :Cat(name, id, masterName) {}

private:
	bool yellow;
};

class Grass
{
public:
	Grass(string name,int id):_name(name), _id(id)
	{
		std::cout << "New Grass " << _name << "_" << _id << std::endl;
	}
private:
	int _id;
	string _name;
};

Cat *GetCat()
{
	return(new Cat("pipi", 1, "Tom"));
}

int main()
{
	cout << "sizeof(VirtulCls) " << sizeof(VirtulCls) << endl;
	cout << "sizeof(Pet) " << sizeof(Pet) << endl;
	cout << "sizeof(Animal) " << sizeof(Animal) << endl;
	cout << "sizeof(Cat) " << sizeof(Cat) << endl;

	Cat *c=GetCat();

	cout << "c adress " << c << endl;

	Animal *a = c;
	cout << "a adress " << a << endl;
	a->Eat();

	Pet *p = c;
	cout << "p adress " << p << endl;

	p->Play();

	Pet *p2 = dynamic_cast<Pet*>(a);
	cout << "p2 adress " << p2 << endl;
	p2->Play();


	char *tmp = new char[160];
	memset(tmp, 1, 160);

	Cat *c2 = static_cast<Cat*>(p);
	cout << "c2 adress " << c2 << endl;
	c2->Run();

	Lion *l = static_cast<Lion*>(a);
	cout << "l adress " << l << endl;
	l->Eat();

	Lion *l2 = dynamic_cast<Lion*>(a);
	cout << "l2 adress " << l2 << endl;
	l2->Eat();

	BossCat *bc = new BossCat("bbos",33,"kaka");

	std::cin.get();
	std::cin.get();
	return 0;
}