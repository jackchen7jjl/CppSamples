#include <iostream>

using namespace std;

class Matrix
{
public:
	double rawData[16];

	double& Get(int row, int column) { return rawData[row + (column * 4)]; }
	const double& Get(int row, int column)const { return rawData[row + (column * 4)]; }

	void Identity()
	{
		Get(0, 0) = 1.0;	Get(0, 1) = 0.0;	Get(0, 2) = 0.0;	Get(0, 3) = 0.0;
		Get(1, 0) = 0.0;	Get(1, 1) = 1.0;	Get(1, 2) = 0.0;	Get(1, 3) = 0.0;
		Get(2, 0) = 0.0;	Get(2, 1) = 0.0;	Get(2, 2) = 1.0;	Get(2, 3) = 0.0;
		Get(3, 0) = 0.0;	Get(3, 1) = 0.0;	Get(3, 2) = 0.0;	Get(3, 3) = 1.0;
	}
};

const Matrix& GetMatrix()
{
	Matrix m;
	m.Identity();
	return m;
}

int main()
{	
	const Matrix &m = GetMatrix();
	std::cout << m.Get(2, 2) << std::endl;
	std::cout << m.Get(2, 2) << std::endl;

	std::cin.get();
	std::cin.get();
	return 0;
}