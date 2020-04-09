#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct Item { //a struct to store an items weight, value, and type
    int weight;
    int value;
    char type;
};

bool compare(struct Item a, struct Item b) { //a compare function that sorts items based on the ratio of their value to weight
    double x = (double)a.value/a.weight;
    double y = (double)b.value/b.weight;
    return (x > y);
}

double Knapsack(int w, vector<Item> x) { //a function to calculate the knapsack value, combing the 0-1 and fractional knapsack

    sort(x.begin(), x.end(), compare); //sorts all items based on ratio

    //uncomment to see ratio of each item
    /*for (unsigned int i = 0; i < x.size(); ++i) {
        cout << x.at(i).value << "  " << x.at(i).weight << " : " << ((double)x.at(i).value / x.at(i).weight) << endl;
    }*/

    int knap_weight = 0; //variable to hold the current knapsack weight
    double final_value = 0; //variable to store final value of all added items

    for (unsigned int i = 0; i < x.size(); ++i) { 
        if (knap_weight + x.at(i).weight <= w) { //The item is added to the knapsack if it can be added fully
            knap_weight += x.at(i).weight;
            final_value += x.at(i).value;
        }
        else { 
            if (x.at(i).type == 'W') { //checks if current item can be divided
                continue;
            }
            int remainder = w - knap_weight; //checks how much weight is left over and adds that from the item to the knapsack
            final_value += x.at(i).value * ((double) remainder / x.at(i).weight);
            break;
        }
    }

    return final_value; //returns the max value obtained
}

int main() {
    ifstream fin;
    int weight_lim = 0, w = 0, v = 0; //variables for maximum weight for the problem, reading in weight, value, and type
    Item item_t; //a re-usable item struct
    vector<Item>items; //a vector to store all items
    char t;

    fin.open("data.txt"); //opens the file and checks for error
    if (fin.fail()) {
        cout << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    while (!fin.eof()) {
        fin >> w >> v >> t; //reads in each row a.k.a. each item
        item_t.weight = w;
        item_t.value = v;
        item_t.type = t;
        items.push_back(item_t); //adds each item to the vector
    }
    
    fin.close();

    items.pop_back(); //cleans up a reading in error where the last entry is copied twice
    for (unsigned int i = 0; i < items.size(); ++i) {//displays each item to the user
        cout << "Item weight: " << items.at(i).weight << "\tItem value: " << items.at(i).value << "\tItem type: " << items.at(i).type << endl;
    }

    srand (time(NULL)); //seeds a random number and randomly creates a maximum weight
    weight_lim = rand() % 50 + 25;
    cout << "The maximum weight limit allowed is: " << weight_lim << endl;

    double knap_final = Knapsack(weight_lim, items); //executes the function to find max knapsack

    cout << "The maximum value we can obtainn is: " << knap_final << endl;

    return 0;
}