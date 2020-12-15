/* Find Proteins from RNA
 This implementation uses more of a stream processing approach.
 */


#include <iostream>
#include "map.h"
#include "vector.h"
#include "foreach.h"

using namespace std;

Vector<string> findProteins(string& rna, Map<string, string> codons);
Map<string, string> getCodons();
const string startCodon = "AUG";
void readUntilStartCodon(string& rna, long& index);
string transcribe(string& rna, long& currentIndex, Map<string, string>& codons);

int main() {
    
    Map<string, string> codons = getCodons();
    string rna = "GCAUGGAUUAAUAUGAGACGACUAAUAGGAUAGUUACAACCCUUAUGUCACCGCCUUGA";
    Vector<string> result = findProteins(rna, codons);
    Vector<string> expected;
    expected.add("methionine, aspartic acid");
    expected.add("methionine, arginine, arginine, leucine, isoleucine, glycine");
    expected.add("methionine, serine, proline, proline");
    
    bool sameSize = result.size() == expected.size();
    cout << "Sizes are equal?: " << sameSize << endl;
    for(int i = 0; i < result.size(); i++) {
        if (i < expected.size()) {
            cout << "element " << i << " is equal: " << (expected[i] == result[i]) << endl;
        } else {
            cout << "there is no element " << i << " in expectation" << endl;
        }
    }
    cout << result << endl;
    return 0;
}

Vector<string> findProteins(string& rna, Map<string, string> codons) {
            
    Vector<string> proteins;
    long currentIndex = 0;
    while (true) {
        readUntilStartCodon(rna,  currentIndex);
        if (currentIndex == string::npos) {
          break;
        }
        proteins.add(transcribe(rna, currentIndex, codons));
    }
    
    return proteins;
}

void readUntilStartCodon(string& rna, long& index) {
    index = rna.find(startCodon, index);
}

string transcribe(string& rna, long& currentIndex, Map<string, string>& codons) {
    string result;
    while(true) {
        string codon = rna.substr(currentIndex, 3);
        currentIndex += 3;

        string aminoAcid = codons[codon];
        
        if (aminoAcid == "stop") {
            break;
        }
        
        result += aminoAcid + ", ";
    }
    return result.substr(0, result.size() - 2); // methionine, asparitic acid
}

Map<string, string> getCodons() {
    Map<string, string> codons;
    codons["GGG"] = "glycine";
    codons["GGA"] = "glycine";
    codons["GAU"] = "aspartic acid";
    codons["CCG"] = "proline";
    codons["CCU"] = "proline";
    codons["AGA"] = "arginine";
    codons["CGA"] = "arginine";
    codons["CUA"] = "leucine";
    codons["AUA"] = "isoleucine";
    codons["AUG"] = "methionine";
    codons["AAU"] = "asparagine";
    codons["AUC"] = "isoleucine";
    codons["UCA"] = "serine";
    codons["UCG"] = "serine";
    codons["GCG"] = "alanine";
    codons["UAA"] = "stop";
    codons["UAG"] = "stop";
    codons["UGA"] = "stop";
    return codons;
}
