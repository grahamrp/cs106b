/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

/*
 Write a program that simulates flipping a coin repeatedly and continues until three consecutive heads are tossed.
 At that point, your program should display the total number of coin flips that were made.
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

string flip() {
    return randomChance(0.5) ? "Head" : "Tail";
}

int main() {
    
    //bool three_consec_heads = false;
    int n_flips = 0;
    int n_heads = 0;
    string result;
    
    while (true) {
        result = flip();
        n_flips++;
        cout << result << endl;
        if (result == "Head") n_heads++; else n_heads = 0;
        if (n_heads >= 3) break;
    }
    cout << "It took " << n_flips << " flips to get 3 consecutive heads." << endl;
    
    return 0;
}
