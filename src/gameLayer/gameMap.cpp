#include "gameMap.h"
#include <asserts.h>

void IntMap::create(int w, int h)
{
	*this = {}; //reset the entire struct
	mapData.resize(w * h);

	this->w = w;
	this->h = h;

	for (auto&i : mapData) { i = {}; } //clear all data
}

int& IntMap::getIntUnsafe(int x, int y) {
	permaAssertCommentDevelopement(mapData.size() == w * h, "Map data not initialised");

	permaAssertCommentDevelopement(x >= 0 && y >= 0 && x < w && y < h, "getBlockUnsafe out of bounds error");

	return mapData[x + y * w];
}

int* IntMap::getIntSafe(int x, int y) {
	permaAssertCommentDevelopement(mapData.size() == w * h, "Map data not initialised");

	if (x < 0 || y < 0 || x >= w || y >= h) { return nullptr; }

	return &mapData[x + y * w];
}
