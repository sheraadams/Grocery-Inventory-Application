#ifndef PROJECTTHREEV2_LISTITEMS_H_
#define PROJECTTHREEV2_LISTITEMS_H_

#pragma once
#include<vector>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
using namespace std;

class ListItems
{

private:

	vector<string>stringVector;

	vector<int>countVector;


public:

	void printItems(map<string, int>& myMap);

	void histogram(map<string, int>& myMap);

	void lookUp(map<string, int>& myMap);

	void printMenu();

};

#endif // PROJECTTHREEV2_LISTITEMS_H_