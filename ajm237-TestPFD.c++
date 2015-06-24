// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <vector>   // vector
#include <list>     // list

#include "gtest/gtest.h"
#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
// ----

TEST(PfdFixture, read_1)
{
    int size = 5;
    string s("4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
    istringstream sin(s);
    vector<int> predList(size);
    vector< list<int> > test(size);
    vector< list<int> > answer(size);
    answer[0].push_back(3);
    answer[4].push_back(3);
    answer[4].push_back(2);
    answer[2].push_back(2);
    answer[2].push_back(4);
    answer[0].push_back(5);
    
    pfd_read(sin, test, predList);

    ASSERT_EQ(predList[0], 0);
    ASSERT_EQ(predList[1], 2);
    ASSERT_EQ(predList[2], 2);
    ASSERT_EQ(predList[3], 1);
    ASSERT_EQ(predList[4], 1);

    for (unsigned int i = 0; i < test.size(); ++i)
    {
        list<int>::iterator testIterB = test[i].begin();
        list<int>::iterator ansIterB = answer[i].begin();
        list<int>::iterator testIterE = test[i].end();
        list<int>::iterator ansIterE = answer[i].end();
        while (testIterB != testIterE)
        {
            ASSERT_EQ(*testIterB, *ansIterB);
            ++testIterB;
            ++ansIterB;
        }
    }
}

TEST(PfdFixture, read_2)
{
    int size = 4;
    string s("2\n3 1 2\n4 1 1\n");
    istringstream sin(s);
    vector<int> predList(size);
    vector< list<int> > test(size);
    vector< list<int> > answer(size);
    answer[0].push_back(4);
    answer[1].push_back(3);
    
    pfd_read(sin, test, predList);

    ASSERT_EQ(predList[0], 0);
    ASSERT_EQ(predList[1], 0);
    ASSERT_EQ(predList[2], 1);
    ASSERT_EQ(predList[3], 1);

    for (unsigned int i = 0; i < test.size(); ++i)
    {
        list<int>::iterator testIterB = test[i].begin();
        list<int>::iterator ansIterB = answer[i].begin();
        list<int>::iterator testIterE = test[i].end();
        list<int>::iterator ansIterE = answer[i].end();
        while (testIterB != testIterE)
        {
            ASSERT_EQ(*testIterB, *ansIterB);
            ++testIterB;
            ++ansIterB;
        }
    }
}

TEST(PfdFixture, read_3)
{
    int size = 4;
    string s("1\n1 2 3 4");
    istringstream sin(s);
    vector<int> predList(size);
    vector< list<int> > test(size);
    vector< list<int> > answer(size);
    answer[2].push_back(1);
    answer[3].push_back(1);
    
    pfd_read(sin, test, predList);

    ASSERT_EQ(predList[0], 2);
    ASSERT_EQ(predList[1], 0);
    ASSERT_EQ(predList[2], 0);
    ASSERT_EQ(predList[3], 0);

    for (unsigned int i = 0; i < test.size(); ++i)
    {
        list<int>::iterator testIterB = test[i].begin();
        list<int>::iterator ansIterB = answer[i].begin();
        list<int>::iterator testIterE = test[i].end();
        list<int>::iterator ansIterE = answer[i].end();
        while (testIterB != testIterE)
        {
            ASSERT_EQ(*testIterB, *ansIterB);
            ++testIterB;
            ++ansIterB;
        }
    }
}

// -----
// eval
// -----

TEST(PfdFixture, eval_1)
{
    int size = 4;

    vector<int> predList(size);
    predList[0] = 2;
    predList[1] = 0;
    predList[2] = 0;
    predList[3] = 0;

    vector< list<int> > test(size);
    test[2].push_back(1);
    test[3].push_back(1);
    
    vector<int> pfd = pfd_eval(test, predList);

    ASSERT_EQ(pfd[0], 2);
    ASSERT_EQ(pfd[1], 3);
    ASSERT_EQ(pfd[2], 4);
    ASSERT_EQ(pfd[3], 1);
}

TEST(PfdFixture, eval_2)
{
    int size = 5;

    vector<int> predList(size);
    predList[0] = 1;
    predList[1] = 2;
    predList[2] = 0;
    predList[3] = 2;
    predList[4] = 0;

    vector< list<int> > test(size);
    test[3].push_back(2);
    test[4].push_back(2);
    test[0].push_back(4);
    test[2].push_back(4);
    test[2].push_back(1);
    
    vector<int> pfd = pfd_eval(test, predList);

    ASSERT_EQ(pfd[0], 3);
    ASSERT_EQ(pfd[1], 1);
    ASSERT_EQ(pfd[2], 4);
    ASSERT_EQ(pfd[3], 5);
    ASSERT_EQ(pfd[4], 2);
}

TEST(PfdFixture, eval_3)
{
    int size = 4;

    vector<int> predList(size);
    predList[0] = 0;
    predList[1] = 0;
    predList[2] = 0;
    predList[3] = 0;

    vector< list<int> > test(size);
    
    vector<int> pfd = pfd_eval(test, predList);

    ASSERT_EQ(pfd[0], 1);
    ASSERT_EQ(pfd[1], 2);
    ASSERT_EQ(pfd[2], 3);
    ASSERT_EQ(pfd[3], 4);
}

// -----
// print
// -----

TEST(PfdFixture, print_1) 
{
    ostringstream w;
    vector<int> test(5);
    test[0] = 1;
    test[1] = 5;
    test[2] = 3;
    test[3] = 2;
    test[4] = 4;
    pfd_print(w, test);
    ASSERT_EQ("1 5 3 2 4", w.str());
}

TEST(PfdFixture, print_2) 
{
    ostringstream w;
    vector<int> test(3);
    test[0] = 2;
    test[1] = 1;
    test[2] = 3;
    pfd_print(w, test);
    ASSERT_EQ("2 1 3", w.str());
}

TEST(PfdFixture, print_3) 
{
    ostringstream w;
    vector<int> test(10);
    test[0] = 10;
    test[1] = 5;
    test[2] = 2;
    test[3] = 4;
    test[4] = 8;
    test[5] = 3;
    test[6] = 6;
    test[7] = 7;
    test[8] = 1;
    test[9] = 9;
    pfd_print(w, test);
    ASSERT_EQ("10 5 2 4 8 3 6 7 1 9", w.str());
}

// -----
// solve
// -----

TEST(PfdFixture, solve_1) {
    istringstream r("5 3\n2 2 4 5\n4 2 1 3\n1 1 3");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 1 4 5 2", w.str());}

TEST(PfdFixture, solve_2) {
    istringstream r("4 2\n1 1 4\n2 1 3");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 2 4 1", w.str());}

TEST(PfdFixture, solve_3) {
    istringstream r("4 3\n1 2 2 4\n2 1 3\n3 1 4");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("4 3 2 1", w.str());}

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
