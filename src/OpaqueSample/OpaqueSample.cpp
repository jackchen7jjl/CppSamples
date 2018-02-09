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

typedef struct OpaqueMatrix OpaqueMatrix;

int main()
{	
	Matrix *m = new Matrix();
	m->Identity();
	OpaqueMatrix *om = (OpaqueMatrix*)m;

	std::cout << ((Matrix*)om)->Get(2, 2) << std::endl;
	std::cout << ((Matrix*)om)->Get(3, 3) << std::endl;

	std::cin.get();
	std::cin.get();
	return 0;
}