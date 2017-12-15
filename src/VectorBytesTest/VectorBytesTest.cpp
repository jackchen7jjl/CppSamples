#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include "FastByteArray.h"
#include <vector>

int main()
{		
	uint numCnts = 100000000;
	FastByteArray fb(numCnts * 4);
	std::vector<uint> vcs(numCnts);

	long long sum = 0;

	clock_t clc0 = clock();
	for (int i = 0; i < numCnts; i++)
	{
		fb.si32(i,i*4);
	}	

	fb.SetPosition(0);

	for (int i = 0; i < numCnts; i++)
	{
		sum += fb.li32(i * 4);
	}

	clock_t clc1 = clock();
	std::cout << "FastByteArray:  " << (clc1 - clc0) << ", " << sum << std::endl;
	sum = 0;

	clc0 = clock();
	for (int i = 0; i < numCnts; i++)
	{
		vcs[i] = i;
	}

	for (int i = 0; i < numCnts; i++)
	{
		sum += vcs[i];
	}

	clc1 = clock();
	std::cout << "vector<float>:  " << (clc1 - clc0) << ", " << sum << std::endl;

	std::cin.get();
	std::cin.get();
	return 0;
}