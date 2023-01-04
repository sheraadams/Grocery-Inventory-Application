# Grocery-Project
Grocery Project reads a text file, counts the unique items, creates a histogram .dat file, and lets users lookup items and their stats.

This project reads a file called “CS210_Project_Three_Input_File.txt” that contains names of grocery items that were recently sold. I designed my program to start by first reading the text file to a vector.  I used two functions to copy the unique names and occurrences to two new vectors, uniquestrings and countstrings. We use the new vectors to refer to the unique items and their occurrences by index number and we iterate over the vectors to print out a new formatted file, print to console, allow for item look up and print a histogram.

The program first reads the input file and creates a .dat file that lists the unique items and their occurrences. The menu option allows the user to print a histogram, look an item by name, or print a list of all items and their count in an inventory style list.  

![grocery](https://user-images.githubusercontent.com/110789514/210664798-6c1d22e9-ea7a-49ba-a267-c4e79da916b9.png)
