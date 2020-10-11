/*
 * File: main.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include <sstream>
#include "console.h"
#include "simpio.h"

using namespace std;

bool isHaiku(string s1, string s2, string s3);
int lineSyllables(string line);
int syllables(string token);
bool isVowel(char c);
bool finalE(int i, string token);

int main() {
    while(true) {
    string line1 = getLine("Enter line 1");
    string line2 = getLine("Enter line 2");
    string line3 = getLine("Enter line 3");
    string haiku_text = isHaiku(line1, line2, line3)? "is a haiku!" : "isn't a haiku :(";
    cout << line1 << endl << line2 << endl << line3 << endl;
    cout << haiku_text << endl;
    }
    return 0;
}

bool isHaiku(string s1, string s2, string s3) {
    
    cout << lineSyllables(s1) << lineSyllables(s2) << lineSyllables(s3) << endl;
    return lineSyllables(s1) == 5 && lineSyllables(s2) == 7 && lineSyllables(s3) == 5;
}

int lineSyllables(string line) {
    istringstream stream(line);
    string word;
    int totalSyllables = 0;
    while(stream >> word) {
        totalSyllables += syllables(word);
    }
    return totalSyllables;
}


int syllables(string token) {
    int n = 0;
    bool vowelJustSeen = false;
    for(int i = 0; i < token.length(); i++) {
        if(isVowel(token[i])) {
            if(!vowelJustSeen && !finalE(i, token)) n++;
            vowelJustSeen = true;
        } else {
            vowelJustSeen = false;
        }
    }
    
    return (n == 0)? 1 : n;
}

bool finalE(int i, string token) {
    bool isFinalLetter = i == (token.length() - 1);
    bool isE = (token[i] == 'e' || token[i] == 'E');
    return isFinalLetter && isE;
}

bool isVowel(char c) {
    bool is_vowel[CHAR_MAX] = { false }; // initializes all values to false
    
    is_vowel['A'] = true;
    is_vowel['a'] = true;
    is_vowel['E'] = true;
    is_vowel['e'] = true;
    is_vowel['I'] = true;
    is_vowel['i'] = true;
    is_vowel['O'] = true;
    is_vowel['o'] = true;
    is_vowel['U'] = true;
    is_vowel['u'] = true;
    is_vowel['Y'] = true;
    is_vowel['y'] = true;

    return is_vowel[c];
}
