// --------------------------------
// projects/PFD/TestPFD.c++
// Copyright (C) 2015
// Andres Correa Fahad Khokhar
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
// ----

TEST(PFDFixture, read_1) {
    string s("1 1 2\n2 0");
    istringstream sin(s);
    vector<vertex> testGraph = PFD_read(2, 2, sin);
    ASSERT_EQ( 1, testGraph.at(0).taskNumber);
    ASSERT_EQ( 2, testGraph.at(1).taskNumber);
    ASSERT_EQ(1, testGraph.at(0).numDependencies);
    ASSERT_EQ(0, testGraph.at(1).numDependencies);

}

TEST(PFDFixture, read_2) {
    string s("1 1 2\n2 0");
    istringstream sin(s);
    vector<vertex> testGraph = PFD_read(2, 2, sin);
    ASSERT_EQ( 1, testGraph.at(0).taskNumber);
    ASSERT_EQ( 2, testGraph.at(1).taskNumber);
    ASSERT_EQ(1, testGraph.at(0).numDependencies);
    ASSERT_EQ(0, testGraph.at(1).numDependencies);

}

TEST(PFDFixture, read_3) {
    string s("1 1 2\n2 0");
    istringstream sin(s);
    vector<vertex> testGraph = PFD_read(2, 2, sin);
    ASSERT_EQ( 1, testGraph.at(0).taskNumber);
    ASSERT_EQ( 2, testGraph.at(1).taskNumber);
    ASSERT_EQ(1, testGraph.at(0).numDependencies);
    ASSERT_EQ(0, testGraph.at(1).numDependencies);

}
    
// ----
// eval
// ----


TEST(PFDFixture, eval_1) {
	vector<vertex> graph (3);
	graph.at(0).taskNumber = 1;
	graph.at(1).taskNumber = 2;
	graph.at(2).taskNumber = 3;

	graph.at(0).numDependencies = 1;
	graph.at(1).numDependencies = 1;
	graph.at(2).numDependencies = 0;

	graph.at(1).successors.push_back(1);
	graph.at(2).successors.push_back(2);

    vector<int> orderedTask = PFD_eval(graph);
    vector<int> ordered;
    ordered.push_back(3);
    ordered.push_back(2);
    ordered.push_back(1);
    ASSERT_EQ(ordered, orderedTask);}

TEST(PFDFixture, eval_2) {
	vector<vertex> graph (4);
	graph.at(0).taskNumber = 1;
	graph.at(1).taskNumber = 2;
	graph.at(2).taskNumber = 3;
	graph.at(3).taskNumber = 4;

	graph.at(0).numDependencies = 1;
	graph.at(1).numDependencies = 1;
	graph.at(2).numDependencies = 0;
	graph.at(3).numDependencies = 0;

	graph.at(2).successors.push_back(2);
	graph.at(3).successors.push_back(1);

    vector<int> orderedTask = PFD_eval(graph);
    vector<int> ordered;
    ordered.push_back(3);
    ordered.push_back(2);
    ordered.push_back(4);
    ordered.push_back(1);
    ASSERT_EQ(ordered, orderedTask);}

TEST(PFDFixture, eval_3) {
	vector<vertex> graph (4);
	graph.at(0).taskNumber = 1;
	graph.at(1).taskNumber = 2;
	graph.at(2).taskNumber = 3;
	graph.at(3).taskNumber = 4;

	graph.at(0).numDependencies = 2;
	graph.at(1).numDependencies = 0;
	graph.at(2).numDependencies = 0;
	graph.at(3).numDependencies = 0;

	graph.at(2).successors.push_back(1);
	graph.at(3).successors.push_back(1);

    vector<int> orderedTask = PFD_eval(graph);
    vector<int> ordered;
    ordered.push_back(2);
    ordered.push_back(3);
    ordered.push_back(4);
    ordered.push_back(1);
    ASSERT_EQ(ordered, orderedTask);}

// -----
// print
// -----

TEST(PFDFixture, print_1) {//input 5 0
    ostringstream w;

    int numVertices = 5;
    vector<int> result;
        for(int x = 0; x < numVertices; ++x)
            result.push_back(x + 1);

    PFD_print(result, w);

    ASSERT_EQ("1 2 3 4 5\n", w.str());}

TEST(PFDFixture, print_2) {//input 3 2 \n 1 1 2 \n 2 1 3
    ostringstream w;

    vector<int> result;
        for(int x = 3; x > 0; --x)
            result.push_back(x);

    PFD_print(result, w);

    ASSERT_EQ("3 2 1\n", w.str());}

TEST(PFDFixture, print_3) {//input 4 1 \n 1 2 3 4
    ostringstream w;

    vector<int> result;
    result.push_back(2);
    result.push_back(3);
    result.push_back(4);
    result.push_back(1);

    PFD_print(result, w);
    ASSERT_EQ("2 3 4 1\n", w.str());}

// -----
// solve
// -----

TEST(PFDFixture, solve_1) {
    istringstream r("4 1\n 1 2 3 4");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("2 3 4 1\n", w.str());}

TEST(PFDFixture, solve_2) {
    istringstream r("4 2\n 1 1 4\n 2 1 3");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("3 2 4 1\n", w.str());}

TEST(PFDFixture, solve_3) {
    istringstream r("5 0\n");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("1 2 3 4 5\n", w.str());}


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



% g++-4.8 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall PFD.c++ TestPFD.c++ -o TestPFD -lgtest -lgtest_main -lpthread



% valgrind TestPFD        >  TestPFD.out 2>&1
% gcov-4.8 -b PFD.c++     >> TestPFD.out
% gcov-4.8 -b TestPFD.c++ >> TestPFD.out



% cat TestPFD.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestPFD
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from PFD
[ RUN      ] PFD.read
[       OK ] PFD.read (31 ms)
[ RUN      ] PFD.eval_1
[       OK ] PFD.eval_1 (5 ms)
[ RUN      ] PFD.eval_2
[       OK ] PFD.eval_2 (3 ms)
[ RUN      ] PFD.eval_3
[       OK ] PFD.eval_3 (3 ms)
[ RUN      ] PFD.eval_4
[       OK ] PFD.eval_4 (3 ms)
[ RUN      ] PFD.print
[       OK ] PFD.print (17 ms)
[ RUN      ] PFD.solve
[       OK ] PFD.solve (10 ms)
[----------] 7 tests from PFD (88 ms total)

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
File 'PFD.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'PFD.c++.gcov'
...
File 'TestPFD.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestPFD.c++.gcov'
...
*/
