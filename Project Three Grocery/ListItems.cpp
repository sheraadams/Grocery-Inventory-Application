#include <iostream>
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "ListItems.h"
#include<map>

using namespace std;

// print a histogram of all items and their counts
void ListItems::histogram(map<string, int>& myMap)
{
    map<string, int> ::iterator it;
    for (it = myMap.begin(); it != myMap.end(); ++it)
    {

        // get the number of items sold at each index
        int numAsterisks = it->second;

        // print out the result
        std::cout << it->first << ' ';

        for (int i = 0; i < numAsterisks; i++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

// print a list of all items and their numeric counts
void ListItems::printItems(map<string, int>& myMap)
{
    map<string, int> ::iterator it;
    for (it = myMap.begin(); it != myMap.end(); it++)
    {
        std::cout << it->first
            << ' '
            << it->second
            << std::endl;
    }
}

// look up a list item and get its count
void ListItems::lookUp(map<string, int>& myMap)
{
    // get product to lookup
    string userString;

    cout << "Enter a product to get statistics: ";

    try {

        std::cin >> userString;
        cout << endl;
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(400, '\n');

            cout << "Invalid Choice. Please choose a valid menu option." << endl;

            continue;
        }
    }
    catch (...) {
        cout << "Invalid Input";
    }



    // convert userstring to camelcase to match the list format for searching
    // using boolean to 
    bool incorrect = true;

    for (int i = 0; userString[i] != '\0'; i++)
    {
        if (std::isalpha(userString[i]))
        {
            if (incorrect)
            {
                // convert first index to upper
                userString[i] = std::toupper(userString[i]);
            }
            else
            {
                // convert remaining index to lower
                userString[i] = std::tolower(userString[i]);
            }
            incorrect = false;
        }
        else if (userString[i] == ' ')
        {
            incorrect = true;
        }
    }
    // once converted to camelcase, continue to search word
    if (!(incorrect))
    {
        // iterate through the map 
        for (auto& it : myMap)
        {
            if (it.first == userString)
            {
                cout << it.second;
                cout << ": ";
                cout << it.first;
            }
        }
    }
    else
    {
        cout << "Please check item name." << endl;
    }

}


// prints the menu when called 
void ListItems::printMenu()

{
    cout << endl;
    cout << "**********************************************************" << endl;
    cout << "*                   Select an option                     *" << endl;
    cout << "**********************************************************" << endl;
    cout << "*               [1] Lookup Item Purchase info            *" << endl;
    cout << "*               [2] Print Inventory                      *" << endl;
    cout << "*               [3] Display Histogram                    *" << endl;
    cout << "*               [4] Exit Application                     *" << endl;
    cout << "**********************************************************" << endl;

    cout << endl;

    return;
}

