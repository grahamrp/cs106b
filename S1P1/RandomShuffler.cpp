/*
 * File:
 * ----------------------
 */


#include <iostream>
#include "random.h"
using namespace std;

string RandomShuffle(string input) {
    
    if (input.empty()) return "";
    
    int randomPick = randomInteger(0, input.length() - 1);
    return input[randomPick] + RandomShuffle(input.erase(randomPick, 1));
    
}

int main() {

    while(true) {
        string str;
        cout << "Enter a string to be shuffled:";
        cin >> str;
        cout << RandomShuffle(str) << endl;
    }

    return 0;
}

