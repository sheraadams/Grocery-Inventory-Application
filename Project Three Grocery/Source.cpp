// to use current time for time stamping, disable warning 4996
#pragma warning(disable : 4996)
#ifndef UNIQUES_HPP
#define UNIQUES_HPP

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
#include <map>

using namespace std;

// Borroweed template to check if vector items are unique from https://stackoverflow.com/questions/28100712/better-way-of-counting-unique-item
// template takes in a vector and creates a new vector that gets unique values and adds only those to a new vector
template<typename T>

std::vector<T>unique_values(std::vector<T>& input_vec)
{
    std::vector<T> uniques(input_vec.size());
   
    typename std::vector<T>::iterator it;
  
    it = std::unique_copy(input_vec.begin(), input_vec.end(), uniques.begin());
  
    std::sort(uniques.begin(), it);
  
    it = std::unique_copy(uniques.begin(), it, uniques.begin());

    uniques.resize(std::distance(uniques.begin(), it));
  
    return uniques;
}

// template takes in a vector and creates a new vector that contains the number of occurrances of the unique values from the input
template<typename T>
std::vector<int> count_unique_values(std::vector<T>& input_vec) 
{
    std::vector<T> uniques = unique_values<T>(input_vec);
    
    std::vector<int> counts(uniques.size());
   
    for (size_t i = 0; i < counts.size(); ++i)
        counts[i] = std::count(input_vec.begin(), input_vec.end(), uniques[i]);
   
    return counts;
}


#endif

int main()
{
    // instantiate class objects
    ListItems menuObj;
    ListItems listObj;
    ListItems printObj;
    ListItems histObj;

    // set the display color to neon green
    system("Color 0A");

    // create two vectors to hold the files data
    vector<string> productList;
    vector<string> uniqueList;

    // create ifstrem object to read the text file
    ifstream productsFS;
    string product;

    // open the text file
    productsFS.open("CS210_Project_Three_Input_File.txt");

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

    // create a vecctor from the unique values
    std::vector<std::string> uniquestrings = unique_values<std::string>(productList);

    // create a vector for the count of each unique value
    std::vector<int> countstrings = count_unique_values<std::string>(productList);

    // create object open outstream, open file for writing
    ofstream outStream;

    // open frquency.dat for writing
    outStream.open("Frequency.dat");

    // iterate through the vectors and send to outstream, writing to .dat file the unuque string and its count
    for (int i = 0; i < uniquestrings.size(); i++)
    {
        {
            outStream << uniquestrings.at(i) << " " << countstrings.at(i) << endl;
        }
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

    // declare a map to combine the two vectors
    std::map< string, int > merged_map;

    // create a map of the two vectors
    std::transform(uniquestrings.begin(), uniquestrings.end(), countstrings.begin(),
        std::inserter(merged_map, merged_map.end()), std::make_pair<string const&, int const&>);

    // initiate swtich menu options to get item stats, print inventory, print histogram or exit
    bool gettingInput = true;

    // command to get input
    int command;

    do
    {
        // check for valid input
        try {

            menuObj.printMenu();

            std::cin >> command;
            cout << endl;
            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(400, '\n');

                cout << "Invalid Choice. Please choose a valid menu option." << endl;

                continue;
            }
            if ((command > 5) || (command <= 0))
            {
                throw (command);
            }
        }
        catch (...) {

            menuObj.printMenu();
        }

        // switch menu option 1 lets the user lookup an item and find out total number sold 
        if (command == 1)
        {
            cout << "**********************************************************" << endl;
            cout << "*                       Item Lookup                      *" << endl;
            cout << "**********************************************************" << endl;
            
            // call lookup function with map as a parameter
            listObj.lookUp(merged_map);

        }
        //print inventory function prints a list of all items sold and their quantity
        if (command == 2)
        {

            cout << "**********************************************************" << endl;
            cout << "*                     Print Inventory                    *" << endl;
            cout << "**********************************************************" << endl;
           
            // call print items function with map as a parameter
            printObj.printItems(merged_map);

        }
        // Print histogram prints out a list of all unique items and one asterisk per item sold
        if (command == 3)
        {

            cout << "**********************************************************" << endl;
            cout << "*                  Histogram Product Data                *" << endl;
            cout << "**********************************************************" << endl;

            // call histogram function with map as a parameter
            histObj.histogram(merged_map);

        }
        // exit the program switch option 4
        if (command == 4)
        {

            cout << "**********************************************************" << endl;
            cout << "*                   Now Exiting Program                  *" << endl;
            cout << "**********************************************************" << endl;
          
            gettingInput = false;

        }

        // loop continues until user enters 4 to quit
    } while (gettingInput == true);


    return 0;

}