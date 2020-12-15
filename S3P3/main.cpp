/*
 * File: main.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "foreach.h"
#include "vector.h"
#include "lexicon.h"
using namespace std;

// drop a letter from a string at a particular index
string drop(string s, int i) {
    return s.substr(0, i) + s.substr(i + 1);
}

Vector<string> permutations(string soFar, string rest) {
    Vector<string> out;
    if (rest.empty()) {
        out += soFar;
    } else {
        
        for (int i = 0; i < rest.length(); i++) {
            out += permutations(soFar + rest[i], drop(rest, i));
        }
    }
    return out;
}

bool findAnagram(string letters, Lexicon& english, Vector<string>& words);

int main() {
    cout << permutations("", "ABC") << endl;;
    return 0;

}

/*
 bool findAnagram(string letters, Lexicon& english,
                               Vector<string>& words);
 
 
 Strip spaces
 For each letter in the provided letters bag
    Take it as first letter in a prospective anagram
    If validWord add it to the output vector and call optimistically with the remaining letters
    If not validWord, take the next letter
 */
