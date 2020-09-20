/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

/*
 */

#include <iostream>
#include "console.h"
using namespace std;

int main() {
    
    // Combinations
    int c(int n, int k);

    for (int n = 0; n < 10; n++ ) {
        for (int k = 0; k <= n; k++)
            cout << c(n, k) << " ";
        cout << endl;
        
        
    }

    return 0;
}

int c(int n, int k) {
    if (k == 0 || k == n)  {
        return 1;
    } else {
        return c(n - 1, k - 1) + c(n - 1, k);
    }
}
