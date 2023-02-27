#ifndef DATA_H
#define DATA_H

#pragma once
#include<vector>
#include <string>
#include <map>
using namespace std;

class Data
{

private:
	vector<string>stringVector;
	vector<int>countVector;

public:
	Data();
	map<string, int> listMap;
	// setter
	void SetMap(map<string, int> &myMap);
	// getter
	map<string, int> GetMap();
	void PrintItems();
	void Histogram();
	void LookUp();
	void PrintMenu();
	map<string, int> ReadTextFile();
};

#endif 