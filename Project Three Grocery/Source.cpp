#include <iostream>
#include <cstring>
#include <string>
#include "data.h"


using namespace std;
int main()
{
    system("Color 0A");
    // initiate swtich menu options to get item stats, print inventory, print histogram or exit
    bool gettingInput = true;

    // command to get input
    int command;
  
    // call data class to read in file, write the file and save the data as a map 
    Data data;
    do
    {
        // check for valid input
        try {

            data.PrintMenu();

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
                throw (command);
            
        }
        catch (...) {

            data.PrintMenu();
        }
        // switch menu option 1 lets the user lookup an item and find out total number sold 
        if (command == 1)
        {        
            // call lookup function
            data.LookUp();

        }
        //print inventory function prints a list of all items sold and their quantity
        if (command == 2)
        {    
            // call print items function
            data.PrintItems();

        }
        // Print histogram prints out a list of all unique items and one asterisk per item sold
        if (command == 3)
        {
            // call histogram function
            data.Histogram();

        }
        // exit the program 
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