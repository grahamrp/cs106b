/*
 * File: main.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "foreach.h"
#include "vector.h"
#include "set.h"
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

Vector<string> subsets(string soFar, string rest) {
    Vector<string> out;
    if (rest.empty()) {
        out += soFar;
    } else {
        
        out += subsets(soFar + rest[0], rest.substr(1));
        out += subsets(soFar, rest.substr(1));
    }
    return out;
}

bool findAnagramRec(string candidate, string rest, Vector<string>& words, Set<string>& english) {
    
    if (english.contains(candidate)) {
        if (rest == "" || findAnagramRec("", rest, words, english)) {
            words.add(candidate);
            return true;
        }
    }
    for (int i = 0; i < rest.length(); i++) {
        if (findAnagramRec(candidate + rest[i], drop(rest, i), words, english)) return true;
    }
    
    return false;
}

bool findAnagram(string letters, Set<string>& english, Vector<string>& words) {
    return findAnagramRec("", letters, words, english);
}

int main() {
    Set<string> english;
    english += "the", "mona", "lisa";
    Vector<string> words;
    cout << findAnagram("thealis", english, words) << endl;
    cout << words << endl;
    return 0;

}

/*
 it's a subsets problem?
 
 base case: are all the letters allocated to the vector?
 
 
 Strip spaces
 For each letter in the provided letters bag
    Take it as first letter in a prospective anagram
    If validWord add it to the output vector and call optimistically with the remaining letters
    If not validWord, take the next letter
 */
