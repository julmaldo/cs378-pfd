
#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

#define TEST_SIZE 1

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <vector>
#include <queue>
#include <algorithm> //for_each
#include <cstdio> //for NULL
using namespace std;

#include "PFD.h"

// ----
// main
// ----

int main () {
    
    int test_size = TEST_SIZE;

    while(test_size-- != 0)
    {

       solve_PFD(cin, cout);
        cout << endl << endl;
    }
    
    return 0;
}



/*
% g++-4.8 -pedantic -std=c++11 -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz
% cat RunCollatz.in
1 10
100 200
201 210
900 1000
% RunCollatz < RunCollatz.in > RunCollatz.out
% cat RunCollatz.out
1 10 1
100 200 1
201 210 1
900 1000 1
% doxygen -g
// That creates the file Doxyfile.
// Make the following edits to Doxyfile.
// EXTRACT_ALL            = YES
// EXTRACT_PRIVATE        = YES
// EXTRACT_STATIC         = YES
% doxygen Doxyfile
// That creates the directory html/.
*/
