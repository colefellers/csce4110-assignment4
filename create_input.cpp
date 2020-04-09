/*
Description: This program makes inputs to be usedd with program 'assignment4.cpp'. It writes all item data to a file 'data.txt'. 
             Each row will represent a different item. The first column is each items weight, the second its value, and the third
             its type (indivsable or divisable). It will prompt the user to enter in the total number of items desired and how many
             of each type. If invalid amounts are entered the program will notify the user and prompt for the values again.
             To compile: g++ create_input.cpp
             To run: ./a.out
*/
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

int main() {
    
    int total = 0, whole = 0, fraction = 0, temp1 = 0, temp2 = 0; //variables used for total items, # of indivisable items, # of divisable items, and two re-usable variables
    ofstream fout; //for outputting to file

    fout.open("data.txt"); //opens file and checks for error
    if(fout.fail()) {
        cout << "Failed to create output file" << endl;
        exit(EXIT_FAILURE);
    }

    srand (time(NULL)); //seeding the random numbers for creating weights and value for each item

    while (1) {
        cout << "Please enter how many total items you would like: ";
        cin  >> total;
        if (total <= 0) {
            cout << "Invalid number of items entered" << endl;
            continue;
        }
        cout << "Please enter how many 0-1 (indavisable) items you would like: ";
        cin  >> whole;
        cout << "Please enter how many fractional (divisable) items you would like: ";
        cin  >> fraction;

        if (total != whole + fraction) { //checks that user input is valid
            cout << "\nNumber of whole and fractional items must equal number of total items entered\n" << endl;
             continue;
        }
        else if (total == 0 && whole == 0 && fraction == 0) {
            cout << "\nNo values entered\n" << endl;
            continue;
        }
        else {
            break;
        }
    }


    for (int i = 0; i < whole; ++i) {
        temp1 = rand() % 15 + 5; //creating weight of indivisable items
        temp2 = rand() % 50 + 10; //creating value for indivisable items
        cout << "Item weight: " << temp1 << "\tItem value: " << temp2 << endl;
        fout << temp1 << " " << temp2 << " W\n";
    }
    for (int i = 0; i < fraction; ++i) {
        temp1 = rand() % 15 + 5; //creating weight of divisable items
        temp2 = rand() % 50 + 10; //creaint value for divisable items
        cout << "Item weight: " << temp1 << "\tItem value: " << temp2 << endl;
        fout << temp1 << " " << temp2 << " F\n";
    }

    fout.close();

    return 0;
}