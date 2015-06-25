// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>   // vector

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
// ----

TEST(PFDFixture, first_read_1) {
        string s("5 4");
        pair<int, int> f = make_pair(5, 4);

        pair<int, int> p = pfd_first_read(s);
        ASSERT_EQ(f, p);}

TEST(PFDFixture, first_read_2) {
        string s("4 3");
        pair<int, int> f = make_pair(4, 3);

        pair<int, int> p = pfd_first_read(s);
        ASSERT_EQ(f, p);}

TEST(PFDFixture, first_read_3) {
        string s("9 6");
        pair<int, int> f = make_pair(9, 6);

        pair<int, int> p = pfd_first_read(s);
        ASSERT_EQ(f, p);}

TEST(PFDFixture, read_1) {
    	string s("3 2 1 5");
	
   	pair<int, int> f = make_pair(3, 2);
	vector<int> sec = {1, 5}; 
	
    	pair<pair<int, int>, vector <int> > p = pfd_read(s);
	pair<pair<int, int>, vector <int> > q = make_pair(f, sec);
    	ASSERT_EQ(p, q);}

TEST(PFDFixture, read_2) {
        string s("2 2 5 3");
        
        pair<int, int> f = make_pair(2, 2);
        vector<int> sec = {3, 5};

        pair<pair<int, int>, vector <int> > p = pfd_read(s);
        pair<pair<int, int>, vector <int> > q = make_pair(f, sec);
        ASSERT_EQ(p, q);}

TEST(PFDFixture, read_3) {
        string s("4 1 3");
        
        pair<int, int> f = make_pair(4, 1);
        vector<int> sec = {3};

        pair<pair<int, int>, vector <int> > p = pfd_read(s);
        pair<pair<int, int>, vector <int> > q = make_pair(f, sec);
        ASSERT_EQ(p, q);}

TEST(PFDFixture, read_4) {
        string s("5 1 1");
        
        pair<int, int> f = make_pair(5, 1);
        vector<int> sec = {1};

        pair<pair<int, int>, vector <int> > p = pfd_read(s);
        pair<pair<int, int>, vector <int> > q = make_pair(f, sec);
        ASSERT_EQ(p, q);}
TEST(PFDFixture, eval_1) {
    std::vector<vector <int> > c= {
                                {3,5},
                                {},
                                {2,4},
                                {},
                                {2,3}
                                };
    std::vector<int> v = {0,2,2,1,1};
    std::vector<int> o = {1, 5, 3, 2, 4};
    ASSERT_EQ(o, pfd_eval(v,c));}

TEST(PFDFixture, eval_2) {
    std::vector<vector <int> > c= {
                                {},
                                {},
                                {1},
                                {1},
                                };
    std::vector<int> v = {2,0,0,0};
    std::vector<int> o = {2,3,4,1};
    ASSERT_EQ(o, pfd_eval(v,c));}

TEST(PFDFixture, eval_3) {
    std::vector<vector <int> > c= {
                                {},
                                {},
                                {2},
                                {1},
                                };
    std::vector<int> v = {1,1,0,0};
    std::vector<int> o = {3,2,4,1};
    ASSERT_EQ(o, pfd_eval(v,c));}

// ----
// eval
// ----
/*
TEST(PFDFixture, eval_1) {
	int i = 1;
	vector<int> j = 
    	const int v = pfd_eval(1, 10);
    	ASSERT_EQ(20, v);}
*/
// -----
// print
// -----

TEST(PFDFixture, print_1) {
    	ostringstream w;
	vector<int> p = {1, 2, 3};
    	pfd_print(w, p);
    	ASSERT_EQ("1 2 3 \n", w.str());}

TEST(PFDFixture, print_2) {
        ostringstream w;
        vector<int> p = {4, 5, 6, 7};
        pfd_print(w, p);
        ASSERT_EQ("4 5 6 7 \n", w.str());}

TEST(PFDFixture, print_3) {
        ostringstream w;
        vector<int> p = {8, 9};
        pfd_print(w, p);
        ASSERT_EQ("8 9 \n", w.str());}

// -----
// solve
// -----

TEST(PFDFixture, solve_1) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4 \n", w.str());}
TEST(PFDFixture, solve_2) {
    istringstream r("4 1\n1 2 3 4\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("2 3 4 1 \n", w.str());}
TEST(PFDFixture, solve_3) {
    istringstream r("4 2\n1 1 4\n2 1 3\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 2 4 1 \n", w.str());}


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
