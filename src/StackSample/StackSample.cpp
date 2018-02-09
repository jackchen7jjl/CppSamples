//#include <iostream>

//using namespace std;

//class Matrix
//{
//public:
//	double rawData[16];
//
//	double& Get(int row, int column) { return rawData[row + (column * 4)]; }
//	const double& Get(int row, int column)const { return rawData[row + (column * 4)]; }
//
//	void Identity()
//	{
//		Get(0, 0) = 1.0;	Get(0, 1) = 0.0;	Get(0, 2) = 0.0;	Get(0, 3) = 0.0;
//		Get(1, 0) = 0.0;	Get(1, 1) = 1.0;	Get(1, 2) = 0.0;	Get(1, 3) = 0.0;
//		Get(2, 0) = 0.0;	Get(2, 1) = 0.0;	Get(2, 2) = 1.0;	Get(2, 3) = 0.0;
//		Get(3, 0) = 0.0;	Get(3, 1) = 0.0;	Get(3, 2) = 0.0;	Get(3, 3) = 1.0;
//	}
//};
//
//const Matrix& GetMatrix()
//{
//	Matrix m;
//	m.Identity();
//	return m;
//}

//Matrix MAT;

int __cdecl add(int a, int b, int c)
{
	return a + b + c;
}

int main()
{	
	int a1 = 10, b1 = 5, c1 = 7;

	int d1 = add(a1,b1,c1);

	int e1 = d1 + 1;
	//const Matrix &m = GetMatrix();
	//std::cout << m.Get(2, 2) << std::endl;
	//std::cout << m.Get(2, 2) << std::endl;

	//std::cin.get();
	//std::cin.get();
	return e1;
}