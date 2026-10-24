#pragma once
#include <vector>


struct IntMap
{

	int w = 0;
	int h = 0;

	std::vector<int> mapData;

	void create(int w, int h);

	int& getIntUnsafe(int x, int y);

	int* getIntSafe(int x, int y);


};