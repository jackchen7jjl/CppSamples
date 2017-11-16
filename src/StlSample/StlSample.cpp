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

using CatKey = tuple<bool, bool,string, int>;

int main()
{	
	Cat *cat1 = new Cat("Tom",1);
	Cat *cat2 = new Cat("Lily",2);
	Cat *cat3 = new Cat("lucy",3);

	unordered_map<string, Cat*> cats;
	/*cats["Tom"] = cat1;
	cats["Lily"] = cat2;
	cats["lucy"] = cat3;

	Cat *cat = cats["lucy"];
	cat->Run();

	cat = cats["ops"];

	if (cat == nullptr)
	{
		cout << "ops!" << endl;
	}*/


	map<CatKey, Cat*> cats2;
	CatKey key1(false, false, "Tom", 1);
	cats2[key1] = cat1;

	CatKey key2(true, true, "Lily", 2);
	cats2[key2] = cat2;

	CatKey key3(true, false, "lucy", 3);
	cats2[key3] = cat3;

	CatKey key(false, false, "Tom", 1);
	Cat *cat = cats2[key];
	cat->Run();

	key = CatKey(false, false, "Tom", 2);
	cat = cats2[key];
	cout << cat << endl;

	key = CatKey(true, false, "Tom", 1);
	cat = cats2[key];
	cout << cat << endl;

	delete cat1;
	delete cat2;
	delete cat3;

	std::cin.get();
	std::cin.get();
	return 0;
}