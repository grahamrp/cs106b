#include <iostream>
#include "lexicon.h"
#include "foreach.h"

using namespace std;

string mostXzibitWord(Lexicon& words);
int countSubWords(string word, Lexicon& lex);

int main() {
    Lexicon lex("words_alpha.txt");
    cout << "Most XzibitWord: " << mostXzibitWord(lex) << endl;
    return 0;
}

string mostXzibitWord(Lexicon& words) {
    string best;
    int max = 0;
    
    foreach(string word in words) {
        int nSubWords = countSubWords(word, words);
        if (nSubWords > max) {
            max = nSubWords;
            best = word;
        }
    }
    
    return best;
}

int countSubWords(string word, Lexicon& lex) {
    Set<string> subWords;
    for (int i = 0; i < word.size(); i++) {
        for (int len = 1; len <= word.size() - i; len++) {
            string subWord = word.substr(i, len);
            if (lex.contains(subWord)) subWords.add(subWord);
        }
    }
    
    return subWords.size();
}
