#include <iostream>
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "data.h"
#include<map>
// to use current time for time stamping
#pragma warning(disable : 4996)

using namespace std;

Data::Data()
{
    map<string, int> myMap = ReadTextFile();
    SetMap(myMap);
}
map<string, int> Data::ReadTextFile()
{
    // create two vectors to hold the files data
    vector<string> productList;
    vector<string> uniqueList;

    // create ifstrem object to read the text file
    ifstream productsFS;
    string product;

    // open the text file
    productsFS.open("text.txt");

    // print an error if the file cannot be opened
    if (!productsFS.is_open()) {
        cout << "Could not open file." << endl;
    }
    else
    {
        getline(productsFS, product);

        // read the file to a string varaible
        while (!productsFS.fail())
        {
            // push product varible to vector
            productList.push_back(product);
            getline(productsFS, product);
        }
        // close the file
        productsFS.close();
    }

    /* Adapted from https://stackoverflow.com/questions/28100712/better-way-of-counting-unique-item */
  
    // create a vecctor called uniuques that contains all of the unique values 
    std::vector<string> uniques(productList.size());
    typename std::vector<string>::iterator it;
    it = std::unique_copy(productList.begin(), productList.end(), uniques.begin());
    std::sort(uniques.begin(), it);
    it = std::unique_copy(uniques.begin(), it, uniques.begin());
    uniques.resize(std::distance(uniques.begin(), it));


    // create a vector of the occurence counts for each unique values of the uniques vectopr
    std::vector<int> counts(uniques.size());
    for (size_t i = 0; i < counts.size(); ++i)
        counts[i] = std::count(productList.begin(), productList.end(), uniques[i]);

    // open the outstream and open the file for writing
    ofstream outStream;
    outStream.open("dat.dat");

    // iterate through the vectors and send to outstream, writing to .dat file the unuque string and its count
    for (int i = 0; i < uniques.size(); i++)
    {
        outStream << uniques.at(i) << " " << counts.at(i) << endl;
    }

    // get current date time
    time_t now = time(0);
    char* date_time = ctime(&now);

    // if file successfully written print to console file completed at date/ time.
    if (!outStream.fail())
    {
        cout << "\n* Writing to text file complete.";

        outStream << "\n*File completed:  " << date_time << endl;
    }

    // close the filestream
    outStream.close();

    // create a map to combine the two vectors
    std::map< string, int > merged_map;
    std::transform(uniques.begin(), uniques.end(), counts.begin(),
        std::inserter(merged_map, merged_map.end()), std::make_pair<string const&, int const&>);

    return merged_map;
}
void Data::SetMap(map<string, int> &myMap) 
{ 
    this->listMap = myMap; 
}

map<string, int> Data::GetMap() 
{
    return listMap;
}

// print a histogram of all items and their counts
void Data::Histogram()
{
    cout << "**********************************************************" << endl;
    cout << "*                  Histogram Product Data                *" << endl;
    cout << "**********************************************************" << endl;

    map<string, int> ::iterator it;
    for (it = listMap.begin(); it != listMap.end(); ++it)
    {
        // get the number of items sold at each index
        int numAsterisks = it->second;
        // print out the result
        std::cout << it->first << ' ';
        for (int i = 0; i < numAsterisks; i++)
            cout << "*";        
        cout << endl;
    }
}

// print a list of all items and their numeric counts
void Data::PrintItems()
{
    cout << "**********************************************************" << endl;
    cout << "*                     Print Inventory                    *" << endl;
    cout << "**********************************************************" << endl;

    map<string, int> ::iterator it;
    for (it = listMap.begin(); it != listMap.end(); it++)
    {
        std::cout << it->first
            << ' '
            << it->second
            << std::endl;
    }
}

// look up a list item and get its count
void Data::LookUp()
{
    cout << "**********************************************************" << endl;
    cout << "*                       Item Lookup                      *" << endl;
    cout << "**********************************************************" << endl;

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
    // using boolean to prevent the search until the word is converted to camelcase
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
        for (auto& it : listMap)
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
void Data::PrintMenu()

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

