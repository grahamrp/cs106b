/*
 * File: main.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "vector.h"
#include "foreach.h"
using namespace std;

bool isMeasurable(int target, Vector<int>& weights);
bool RecBalance(Vector<int> left, Vector<int> right, Vector<int> rest);
int sum(Vector<int> v);
Vector<int> tail(Vector<int> v);
Vector<int> add(Vector<int> v, int e);

// Wrapper
bool isMeasurable(int target, Vector<int>& weights) {
    Vector<int> left;
    left += target;
    return RecBalance(left, Vector<int>(), weights);
}


// From a given set of weights, can we get the left and right sides to balance?
bool RecBalance(Vector<int> left, Vector<int> right, Vector<int> weights) {
    
    if (weights.isEmpty()) { 
        return sum(left) == sum(right);
    } else {
        // case with first element on left scale
        // case with first element on right scale
        // case without first element
        return RecBalance(add(left, weights[0]), right, tail(weights)) ||
        RecBalance(left, add(right, weights[0]), tail(weights)) ||
        RecBalance(left, right, tail(weights));
    }
}

int main() {
    
    Vector<int> weights;
    weights += 2, 1;
    
    Vector<int> targets;
    targets += 1, 2, 3, 4, 5, 6;
    
    foreach(int target in targets) {
      string result = isMeasurable(target, weights)? "is measurable" : "is NOT measurable";
      cout << target << " is " << result << " with weights: " << weights << endl;
    }
    
    return 0;
}

// Helper functions
Vector<int> tail(Vector<int> v) {
    v.remove(0);
    return v;
}

Vector<int> add(Vector<int> v, int e) {
    v.add(e);
    return v;
}

int sum(Vector<int> v) {
    int total = 0;
    foreach(int el in v) total += el;
    return total;
}

// Roughing out:

// Provided string implementation
void RecSubsets(string soFar, string rest) {
    if (rest.empty())
        cout << soFar << endl;
    else {
        RecSubsets(soFar + rest[0], rest.substr(1));
        RecSubsets(soFar, rest.substr(1));
    }
}

// Adaption to use vectors (with helper functions)
void RecSubsets(Vector<int> soFar, Vector<int> rest) {
    if (rest.isEmpty())
        cout << "soFar:" << soFar << endl;
    else {
        RecSubsets(add(soFar, rest[0]), tail(rest));
        RecSubsets(soFar, tail(rest));
    }
}
