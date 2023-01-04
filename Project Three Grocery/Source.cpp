#include <iostream>
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#ifndef UNIQUES_HPP
#define UNIQUES_HPP
#include <ctime>
#include <iomanip>
// to use current time, disable warning 4996
#pragma warning(disable : 4996)
#include <algorithm>


using namespace std;

// Borroweed template to check if vector items are unique from https://stackoverflow.com/questions/28100712/better-way-of-counting-unique-item
// Note: there are probably better ways of doing the same thing, but I found this works for well for the purpose


// template takes in a vector and creates a new vector that gets unique values and adds only those to a new vector
template<typename T>

std::vector<T> unique_values(std::vector<T>& input_vec)
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
std::vector<int> count_unique_values(std::vector<T>& input_vec) {

    std::vector<T> uniques = unique_values<T>(input_vec);
    std::vector<int> counts(uniques.size());
    for (size_t i = 0; i < counts.size(); ++i)
        counts[i] = std::count(input_vec.begin(), input_vec.end(), uniques[i]);
    return counts;
}

#endif

void printMenu()

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

int main()
{
    system("Color 02");
    vector<string> productList;
    vector<string> uniqueList;

    ifstream productsFS;
    string product;

    productsFS.open("CS210_Project_Three_Input_File.txt");

    if (!productsFS.is_open()) {
        cout << "Could not open file products.txt." << endl;
    }
    else {
        getline(productsFS, product);

        // while reading the file successfully, take in elements to a vector 
        while (!productsFS.fail()) 
        
        {
            productList.push_back(product);
            getline(productsFS, product);
        }
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
        cout << "\n** Writing to text file complete. \nText file can be found in project folder 'cmake-build-debug'.";

        outStream << "\n*File completed:  " << date_time << endl;
    }
    // close the filestream
    outStream.close();

    // initiate swtich menu options to get item stats, print inventory, print histogram or exit
    bool gettingInput = true;  
    int Ucommand;  
    do {


        // check for valid input
        try {
            printMenu();

            std::cin >> Ucommand;
            cout << endl;
            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(400, '\n');

                cout << "Invalid Choice. Please choose a valid menu option." << endl;

                continue;
            }
            if ((Ucommand > 5) || (Ucommand <= 0))
            {
                throw (Ucommand);
            }
        }
        catch (...) {

            printMenu();;
        }

        // switch menu option 1 lets the user lookup an item and find out total number sold 
        if (Ucommand == 1)
        {
            cout << "**********************************************************" << endl;
            cout << "*                       Item Lookup                      *" << endl;
            cout << "**********************************************************" << endl;

            string userString;



            cout << "Enter a product to get statistics: ";

            std::cin >> userString;
           

            // convert userstring to camercase to match the list format for searching
            bool incorrect = true;
            for (int i = 0; userString[i] != '\0'; i++) 
            {
                if (std::isalpha(userString[i])) 
                {
                    if (incorrect)
                    {
                        userString[i] = std::toupper(userString[i]);
                        incorrect = false;
                    }
                    else 
                    {
                        userString[i] = std::tolower(userString[i]);
                    }
                }
                else if (userString[i] == ' ') 
                {
                    incorrect = true;
                }
            }

            // get the index of the userstring 
            auto it = find(uniquestrings.begin(), uniquestrings.end(), userString);

            int index;

            if (it != uniquestrings.end())
            {
                index = it - uniquestrings.begin();
            }
            else
            {
                index = -1;
            }
            // get the number of items associated with the userstring
            int total = countstrings.at(index);

            // print result to console
            if (total == -1) {
                cout << "Could not find '" << userString << "'. Please check item name." << endl;
            }
            else {
                cout << "Sold today: " << total << " " << userString << endl; // validates correct input AND prints to console the amount of product purchased/located within file
            }

        }
        //print inventory function prints a list of all items sold and their quantity
        if (Ucommand == 2) {

            cout << "**********************************************************" << endl;
            cout << "*                     Print Inventory                    *" << endl;
            cout << "**********************************************************" << endl;

            for (int i = 0; i < uniquestrings.size(); i++)
            {
                {
                    cout << uniquestrings.at(i) << " " << countstrings.at(i) << endl;
                }
            }

        }
        // Print histogram prints out a list of all unique items and one asterisk per item sold
        if (Ucommand == 3) {

            cout << "**********************************************************" << endl;
            cout << "*                  Histogram Product Data                *" << endl;
            cout << "**********************************************************" << endl;


            for (int i = 0; i < uniquestrings.size(); i++)
            {
                {
                    // get the number of items sold at each index
                    int numAsterisks = countstrings.at(i);

                    // print out the result
                    cout << uniquestrings.at(i) << " ";

                    for (int i = 0; i < numAsterisks; i++)
                    {
                        cout << "*";
                    }
                    cout << endl;
                }
            }

        }
        // exit the program switch option 4
        if (Ucommand == 4) {

            cout << "**********************************************************" << endl;
            cout << "*                   Now Exiting Program                  *" << endl;
            cout << "**********************************************************" << endl;
            gettingInput = false;

        } 

        // loop continues until user enters 4 to quit
    } while (gettingInput == true); 

    printMenu();

    return 0;

}