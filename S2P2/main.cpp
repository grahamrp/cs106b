#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "map.h"
#include "vector.h"

using namespace std;

typedef string rnaT;
typedef string protienT;
Vector<string> findProteins(string& rna, Map<string, string> codons);
Vector<rnaT> getEncodingSequences(string rna, Map<string, string>& codons);
unsigned long findStartCodon(string rna, unsigned long start);
unsigned long findEndCodon(string rna, unsigned long start, Vector<string> codons);
Vector<protienT> transcribe(Vector<rnaT> rna, Map<string, string> codons);
protienT transcribe(rnaT rna, Map<string, string> codons);

const int codonLength = 3;

Vector<string> findProteins(string& rna, Map<string, string> codons) {
    Vector<rnaT> sequences = getEncodingSequences(rna, codons);
    Vector<protienT> proteins = transcribe(sequences, codons);
    return proteins;
}

Vector<rnaT> getEncodingSequences(string rna, Map<string, string>& codons) {
    Vector<rnaT> sequences;
    Vector<string> stopCodons;
    
    foreach(string codon in codons) {
        if (codons[codon] == "stop") {
            stopCodons.add(codon);
        }
    }
        
    unsigned long start = 0;
    while ((start = findStartCodon(rna, start)) != string::npos) {
        unsigned long end = findEndCodon(rna, start, stopCodons) + codonLength;
        string segment = rna.substr(start, end - start);
        sequences.add(segment);
        start = end;
    }

    return sequences;
}

unsigned long findStopCodon(string rna, string codon, unsigned long start) {
    unsigned long index = start + 1;
    while (index != string::npos) {
        if ((index - start) % codonLength == 0) {
            return index;
        }
        index = rna.find(codon, index + 1);
    }
    return string::npos;
}

unsigned long findStartCodon(string rna, unsigned long start) {
    string startCodon = "AUG";
    return rna.find(startCodon, start);
}


unsigned long findEndCodon(string rna, unsigned long start, Vector<string> codons) {
    unsigned long minIndex = string::npos;
    foreach(string codon in codons) {
        unsigned long index = findStopCodon(rna, codon, start);
        if (index < minIndex) {
            minIndex = index;
        }
    }
    return minIndex;
}

Vector<protienT> transcribe(Vector<rnaT> rna, Map<string, string> codons) {
    Vector<string> proteins;
    foreach(rnaT sequence in rna) {
        proteins.add(transcribe(sequence, codons));
    }
    return proteins;
}

protienT transcribe(rnaT rna, Map<string, string> codons) {
    protienT result;
    int index = 0;
    while (index < rna.size()) {
        string codon = rna.substr(index, codonLength);
        result += (codons[codon] + ", ");
        index+=codonLength;
    }
    result = result.substr(0, result.size() - 8);
    return result;
}

// Test
bool equals(Vector<string>a, Vector<string> b) {
    if (a.size() != b.size()) return false;
    
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    
    return true;
}

Vector<string> toVector(vector<string> v) {
    Vector<string> V;
    foreach(string s in v) V.add(s);
    return V;
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

TEST_CASE("findProteins") {
    Map<string, string> codons = getCodons();
    string rna = "GCAUGGAUUAAUAUGAGACGACUAAUAGGAUAGUUACAACCCUUAUGUCACCGCCUUGA";
    REQUIRE( equals(findProteins(rna, codons),
                  toVector(vector<string> {
        "methionine, aspartic acid",
        "methionine, arginine, arginine, leucine, isoleucine, glycine",
        "methionine, serine, proline, proline"})));

}

TEST_CASE("getEncodingSequences") {
    Map<string, string> codons = getCodons();
    string rna = "GCAUGGAUUAAUAUGAGACGACUAAUAGGAUAGUUACAACCCUUAUGUCACCGCCUUGA";
    REQUIRE( equals(getEncodingSequences(rna, codons),
                  toVector(vector<string> {
        "AUGGAUUAA",
        "AUGAGACGACUAAUAGGAUAG",
        "AUGUCACCGCCUUGA"})));

}
