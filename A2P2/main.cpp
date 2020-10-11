#include <iostream>
#include <fstream>
#include "map.h"
#include "vector.h"
#include "foreach.h"
#include "random.h"

using namespace std;

typedef Map<string, Vector<char> > CharMap;

CharMap generateCharMap(ifstream& input, int keySize);
string getKey(Vector<char> &buffer, int keySize);
void writeShit(CharMap cmap, int nShit);
string findSeed(CharMap cmap);
char randomChar(Vector<char> chars);
    

int main() {
    
    ifstream input("Hamlet.txt");
    int k = 3;
    
    CharMap cmap = generateCharMap(input, k);
    writeShit(cmap, 2000);
    
    return 0;
}


CharMap generateCharMap(ifstream& input, int keySize) {
    
    Vector<char> buffer;
    CharMap cmap;
    char ch;
    
    while (input.get(ch)) {
        buffer.add(ch);
        if (buffer.size() > keySize) {
            string key = getKey(buffer, keySize);
            cmap[key].add(buffer.get(buffer.size() - 1));
        }
    }
    
    return cmap;
}


string getKey(Vector<char> &buffer, int keySize) {
    
    int endIndex = buffer.size() - 2;
    int startIndex = (endIndex - keySize) + 1;
    string key;
    for (int i = startIndex; i <= endIndex; i++) {
        key += buffer[i];
    }
    return key;
}


void writeShit(CharMap cmap, int nShit) {
    
    string seed = findSeed(cmap);
    cout << seed;
    for (int i = 0; i < nShit; i++) {
        if (!cmap.containsKey(seed)) break;
        
        char nextChar = randomChar(cmap[seed]);
        cout << nextChar;
        seed = seed.substr(1) + nextChar;
    }
    cout << endl;
}


string findSeed(CharMap cmap) {
    
    string seed;
    int maxSize = 0;
    foreach(string key in cmap) {
        if (cmap[key].size() > maxSize) {
            maxSize = cmap[key].size();
            seed = key;
        }
    }
    
    return seed;
}


char randomChar(Vector<char> chars) {
    
    int index = randomInteger(0, chars.size() - 1);
    
    return chars[index];
}
