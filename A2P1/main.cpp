#include <iostream>
#include "lexicon.h"
#include "queue.h"
#include "foreach.h"

using namespace std;

typedef Vector<string> ladderT;

ladderT findShortestLadder(string startWord, string endWord, Lexicon& validWords);
Set<string> connections(string word, Lexicon& validWords);
Set<string> generateCandidates(string word);
Set<string> filterCandidates(Set<string> candidates, Lexicon& validWords);
string replaceChar(string word, int pos, char c);
string lastWord(ladderT ladder);


int main() {
    
    string startWord = "code";
    string endWord = "data";
    Lexicon validWords("words_alpha.txt");
    ladderT sl = findShortestLadder(startWord, endWord, validWords);
    if (sl.isEmpty()) {
        cout << "no solution found" << endl;
    } else {
        cout << "solution found!" << endl << sl.toString() << endl;
    }
    
    return 0;
}


ladderT findShortestLadder(string startWord, string endWord, Lexicon& validWords){
    Lexicon usedWords;
    Queue<ladderT> q;
    q.enqueue(ladderT(1, startWord));
    
    while (!q.isEmpty()) {
        ladderT l = q.dequeue();
        if (lastWord(l) == endWord) {
            return l;
        } else {
            foreach(string word in connections(lastWord(l), validWords)) {
                if (!usedWords.contains(word)) {
                    ladderT l2 = l;
                    l2.add(word);
                    usedWords.add(word);
                    q.enqueue(l2);
                }
            }
        }
    }
    return ladderT();
}


Set<string> connections(string word, Lexicon& validWords) {
    
    Set<string> candidates = generateCandidates(word);
    return filterCandidates(candidates, validWords);
    
}


Set<string> generateCandidates(string word) {
    
    Set<string> candidates;
    for (int i = 0; i < word.length(); i++) {
        for (char l = 'a'; l <= 'z'; l++) {
            candidates.add(replaceChar(word, i, l));
        }
    }
    candidates.remove(word);
    return candidates;
}


Set<string> filterCandidates(Set<string> candidates, Lexicon& validWords) {
    
    Set<string> chosen;
    foreach(string candidate in candidates) {
        if (validWords.contains(candidate)) chosen.add(candidate);
    }
    
    return chosen;
    
}



string replaceChar(string word, int pos, char c) {
    
    word[pos] = c;
    return word;
    
}


string lastWord(ladderT ladder) { return ladder.get(ladder.size() - 1); }
