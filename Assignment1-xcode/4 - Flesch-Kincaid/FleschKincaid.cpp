/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */
#include <cctype>
#include <iostream>
#include <fstream>
#include "console.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "filelib.h"
using namespace std;

bool isWord(string token);
bool isEndOfSentence(string token);
bool isVowel(char c);
bool finalE(int i, string token);
int syllables(string token);
double fleschKincaidScore(int syllables, int words, int sentences);

void test_syllables(string token, int expected_syllables);

int main() {

    string filename = getLine("Enter a filename:");
    while(!fileExists(filename)) {
        cout << filename << " does not exist." << endl;
        filename = getLine("Enter a filename:");
    }
    ifstream file(filename);

    // Configure token scanner
    TokenScanner scanner(file);
    scanner.ignoreWhitespace();
    scanner.addWordCharacters("'");

    int n_words = 0;
    int n_sentences = 0;
    int n_syllables = 0;
    string next_token;
    while(scanner.hasMoreTokens()) {
        next_token = scanner.nextToken();
        n_words += isWord(next_token)? 1 : 0;
        n_sentences += isEndOfSentence(next_token)? 1 : 0;
        n_syllables += syllables(next_token);
    }
    
    cout << "Total syllables: " << n_syllables << endl;
    cout << "Total words: " << n_words << endl;
    cout << "Total sentences: " << n_sentences << endl;
    cout << "Flesch-Kincaid Score: " << fleschKincaidScore(n_syllables, n_words, n_sentences) << endl;
    
    cout << endl;
    test_syllables("apple", 1);
    test_syllables("pear", 1);
    test_syllables("banana", 3);
    test_syllables("bitches", 2);
    test_syllables("me", 1);
    test_syllables("deduce", 2);
    test_syllables("peach", 1);

    return 0;
}

double fleschKincaidScore(int syllables, int words, int sentences) {
    double C0 = -15.59;
    double C1 = 0.39;
    double C2 = 11.8;
    
    syllables = (syllables < 1) ? 1 : syllables;
    words = (words < 1) ? 1 : words;
    sentences = (sentences < 1) ? 1: sentences;
    
    return C0 + (C1 * (words / sentences)) + (C2 * (syllables / words));
}


bool isWord(string token) {
    return isalpha(token[0]);
}

bool isEndOfSentence(string token) {
    char t0 = token[0];
    return ((t0 == '.' || t0 == '?' || t0 == '!'))? true : false;
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

void test_syllables(string token, int expected_syllables) {
    int actual_syllables = syllables(token);
    string result = (actual_syllables == expected_syllables)? "PASS" : "FAIL";
    cout << token << ": " << result  << " expected:" << expected_syllables << ", actual:" << actual_syllables << endl;
}
