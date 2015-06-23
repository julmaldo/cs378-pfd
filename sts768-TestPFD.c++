// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // make_pair, pair
#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// firstLine
// ----

TEST(PFDFixture, firstLine_1) {
    string s("5 4");
    vector<list<int> > vec(0);
    const pair<int, int> p = firstLine(s,vec);
    ASSERT_EQ( 5, p.first);
    ASSERT_EQ(4, p.second);
    ASSERT_EQ(vec.size(), 5);
    ASSERT_TRUE(vec[0].empty());
}

TEST(PFDFixture, firstLine_2) {
    string s("5 0");
    vector<list<int> > vec(0);
    const pair<int, int> p = firstLine(s,vec);
    ASSERT_EQ(5, p.first);
    ASSERT_EQ(0, p.second);
    ASSERT_EQ(vec.size(), 5);
    ASSERT_TRUE(vec[0].empty());
}

TEST(PFDFixture, firstLine_3) {
    string s("0 1");
    vector<list<int> > vec(0);
    const pair<int, int> p = firstLine(s,vec);
    ASSERT_EQ( 0, p.first);
    ASSERT_EQ(1, p.second);
    ASSERT_EQ(vec.size(), 0);
    //ASSERT_TRUE(vec[0].empty());
}


// ----
// pfd_rule
// ----

TEST(PFDFixture, pfd_rule_1) {
    string s("5 1\n");
    vector<list<int> > vec(0);
    const pair<int, int> p = firstLine(s,vec);
    string t("3 2 1 5\n");
    pfd_rule(t, p.first, vec);
    ASSERT_EQ(vec[2].front(), 1);
    ASSERT_EQ(vec[2].back(), 5);
}

TEST(PFDFixture, pfd_rule_2) {
    string s("5 1\n");
    vector<list<int> > vec(0);
    const pair<int, int> p = firstLine(s,vec);
    string t("3 1 1 5\n");
    pfd_rule(t, p.first, vec);
    ASSERT_EQ(vec[2].size(), 1);
    ASSERT_EQ(vec[2].front(), 1);
    ASSERT_NE(vec[2].back(), 5);
}

TEST(PFDFixture, pfd_rule_3) {
    string s("5 1\n");
    vector<list<int> > vec(0);
    const pair<int, int> p = firstLine(s,vec);
    string t("3 3 1 5\n");
    pfd_rule(t, p.first, vec);
    ASSERT_EQ(vec[2].size(), 2);
    ASSERT_EQ(vec[2].front(), 1);
    ASSERT_EQ(vec[2].back(), 5);
}

TEST(PFDFixture, pfd_rule_4) {
    string s("5 1\n");
    vector<list<int> > vec(0);
    const pair<int, int> p = firstLine(s,vec);
    string t("3 0 1 5\n");
    pfd_rule(t, p.first, vec);
    ASSERT_EQ(vec[2].size(), 0);
}

TEST(PFDFixture, pfd_rule_5) {
    string s("5 2\n");
    vector<list<int> > vec(0);
    const pair<int, int> p = firstLine(s,vec);
    string t = "3 2 1 5\n";
    pfd_rule(t, p.first, vec);
    t = "3 2 2 3\n";
    pfd_rule(t, p.first, vec);
    ASSERT_EQ(vec[2].size(), 2);
    ASSERT_EQ(vec[2].front(), 1);
    ASSERT_EQ(vec[2].back(), 5);
}

// -----
// pfd_eval
// -----

TEST(PFDFixture, eval_1) {
    string s("5 4\n");
    vector<list<int> > vec(0);
    list<int> l1;
    const pair<int, int> p = firstLine(s,vec);
    ASSERT_EQ(vec.size(), 5);
    string o = "3 2 1 5\n";
    pfd_rule(o, p.first, vec);
    ASSERT_EQ(vec[2].size(), 2);
    o = "2 2 5 3\n";
    pfd_rule(o, p.first, vec);
    ASSERT_EQ(vec[1].size(), 2);
    o = "4 1 3\n";
    pfd_rule(o, p.first, vec);
    ASSERT_EQ(vec[3].size(), 1);
    o = "5 1 1 \n";
    pfd_rule(o, p.first, vec);
    ASSERT_EQ(vec[4].size(), 1);
    pfd_eval(p.first, l1, vec);
    list<int> l2 = {1, 5, 3, 2, 4};
    ASSERT_EQ(l1, l2);}

TEST(PFDFixture, eval_2) {
    string s("5 3\n");
    vector<list<int> > vec(0);
    list<int> l1;
    const pair<int, int> p = firstLine(s,vec);
    ASSERT_EQ(vec.size(), 5);
    string o = "3 2 1 5\n";
    pfd_rule(o, p.first, vec);
    ASSERT_EQ(vec[2].size(), 2);
    o = "2 2 5 3\n";
    pfd_rule(o, p.first, vec);
    ASSERT_EQ(vec[1].size(), 2);
    pfd_eval(p.first, l1, vec);
    list<int> l2 = {1,4,5,3,2};
    ASSERT_EQ(l1, l2);}

// -----
// print
// -----

TEST(PFDFixture, print_1){
    string s("1 2 3 4 5 6 7 8 9 10\n");
    ostringstream w;
    list<int> li = {1,2,3,4,5,6,7,8,9,10};
    pfd_print(w, li);
    ASSERT_EQ(s, w.str());
}
// -----
// pfd_solve
// -----

TEST(PFDFixture, solve_1) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4\n", w.str());}

TEST(PFDFixture, solve_2) {
    istringstream r("5 0\n3 2 1 5\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2 3 4 5\n", w.str());}

TEST(PFDFixture, solve_3) {
    istringstream r("5 2\n3 2 1 5\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2 4 5 3\n", w.str());}

TEST(PFDFixture, solve_4) {
    istringstream r("4 2\n1 1 4\n2 1 3\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 2 4 1\n", w.str());}

/*

% ls -al /usr/include/gtest/
...
gtest.h
...



% locate libgtest.a
/usr/lib/libgtest.a
...



% locate libpthread.a
...
/usr/lib32/libpthread.a



% locate libgtest_main.a
/usr/lib/libgtest_main.a
...



% g++-4.8 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz        >  TestCollatz.out 2>&1
% gcov-4.8 -b Collatz.c++     >> TestCollatz.out
% gcov-4.8 -b TestCollatz.c++ >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
...
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
...
*/
