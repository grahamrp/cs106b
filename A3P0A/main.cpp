#include <iostream>
#include "set.h"
#include "random.h"
using namespace std;

// Number of Paths Home
int numPathsHome(int street, int avenue) {
    // Base case: we're home.
    if (street == 1 && avenue == 1) return 1;
    // We fell off the map, not a valid path.
    if (street < 1 || avenue < 1) return 0;
    
    // Recursive case.
    return numPathsHome(street - 1, avenue) +
           numPathsHome(street, avenue - 1);
}

// Random Subsets implementation 1
// Uses the basic subsets pattern but instead of generating all subsets "with" and "without"
// the first element, the first element is added (or not) randomly.
Set<int> RecSubsets(Set<int> soFar, Set<int> rest) {
    if (rest.isEmpty()) {
        return soFar;
    }
    else {
        if (randomChance(0.5)) soFar.add(rest.first());
        rest.remove(rest.first());
        return RecSubsets(soFar, rest);
    }
}

Set<int> randomSubsetOf(Set<int>& s) {
    Set<int> soFar;
    return RecSubsets(soFar, s);
}

// Random Subsets implementation 2
// Simpler implementation based on recursive understanding that the solution is
// <maybe include first element>  + random subset of the rest
Set<int> randomSubsetOf2(Set<int> s) {
    // base case
    if (s.isEmpty()) return s;

    // separate first from s
    int first = s.first();
    s -= first;

    return randomChance(0.5)? randomSubsetOf2(s) + first : randomSubsetOf2(s);
}

int main() {
    cout << "numPathsHome: " << numPathsHome(3, 2) << endl << endl;
    Set<int> s;
    s += 1, 2, 3, 4, 5;
    cout << "randomSubset of" << endl << s << endl << "is" << endl << randomSubsetOf(s) << endl;
    cout << "randomSubset2 of" << endl << s << endl << "is" << endl << randomSubsetOf2(s) << endl;

    return 0;
}
