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


// -----
// solve
// -----

TEST(PFDFixture, solve) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4\n", w.str());}
//---------
// update
//---------

TEST(PFDFixture, update) {
    ASSERT_EQ(pfd_update_tasks_list(3), 3);}
    
// ----
// read_first
// ----

TEST(PFDFixture, read_first) {
    string s("5 4\n");
    const int p = pfd_read_first(s);
    ASSERT_EQ( 4, p);}

TEST(PFDFixture, read_first2) {
    string s("100 200\n");
    const int p = pfd_read_first(s);
    ASSERT_EQ(200, p);}

TEST(PFDFixture, read_first3) {
    string s("201 210\n");
    const int p = pfd_read_first(s);
    ASSERT_EQ(210, p);}

TEST(PFDFixture, read_first4)   {
    string s("1 999999\n");
    const int p = pfd_read_first(s);
    ASSERT_EQ(999999, p);}

// ----
// read_rest
// ----

TEST(PFDFixture, read_rest) {
    string s("3 2 1 5\n");
    list<int> q = {3, 2, 1, 5};
    const list<int> p = pfd_read_rest(s);
    ASSERT_TRUE(equal(q.begin(), q.end(), p.begin()));}

TEST(PFDFixture, read_rest2) {
    string s("2 2 5 3\n");
    list<int> q = {2, 2, 5, 3};
    const list<int> p = pfd_read_rest(s);
    ASSERT_TRUE(equal(q.begin(), q.end(), p.begin()));}


TEST(PFDFixture, read_rest3) {
    string s("4 1 3\n");
    list<int> q = {4, 1, 3};
    const list<int> p = pfd_read_rest(s);
    ASSERT_TRUE(equal(q.begin(), q.end(), p.begin()));}


TEST(PFDFixture, read_rest4)   {
    string s("5 1 1\n");
    list<int> q = {5, 1, 1};
    const list<int> p = pfd_read_rest(s);
    ASSERT_TRUE(equal(q.begin(), q.end(), p.begin()));}


//-------
// build_adj_list
//----------
TEST(PFDFixture, build_adj) {
    list<int> q = {3, 2, 1, 5};
    const int p = build_adj_list(q);
    ASSERT_EQ(2, p);}

TEST(PFDFixture, build_adj1) {
    list<int> q = {2, 2, 5, 3};
    const int p = build_adj_list(q);
    ASSERT_EQ(2, p);}

TEST(PFDFixture, build_adj2) {
    list<int> q = {4, 1, 3};
    const int p = build_adj_list(q);
    ASSERT_EQ(1, p);}

TEST(PFDFixture, build_adj3)   {
    list<int> q = {5, 1, 1};
    const int p = build_adj_list(q);
    ASSERT_EQ(1, p);} 

// ----
// eval
// ----

TEST(PFDFixture, eval_1) {
    const int v = pfd_eval();
    ASSERT_EQ(1, v);}

// -----
// print
// -----

TEST(PFDFixture, print) {
    ostringstream w;
    list<int> p = {1, 2, 3, 4};
    pfd_print(w, p);
    ASSERT_EQ("1 2 3 4\n", w.str());}

TEST(PFDFixture, print2) {
    ostringstream w;
    list<int> p = {5, 2, 1, 4};
    pfd_print(w, p);
    ASSERT_EQ("5 2 1 4\n", w.str());}

TEST(PFDFixture, print3) {
    ostringstream w;
    list<int> p = {5, 2, 1, 4, 3, 7};
    pfd_print(w, p);
    ASSERT_EQ("5 2 1 4 3 7\n", w.str());}

TEST(PFDFixture, print4) {
    list<int> p = {1};
    ostringstream w;
    pfd_print(w, p);
    ASSERT_EQ("1\n", w.str());}


     

/*
TEST(PFDFixture, solve2) {
    istringstream r("210 201\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("210 201 89\n", w.str());}

TEST(PFDFixture, solve3) {
    istringstream r("1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 1 1\n", w.str());}

TEST(PFDFixture, solve4) {
    istringstream r("1 1\n200 100\n10 11\n1 2\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 1 1\n200 100 125\n10 11 15\n1 2 2\n", w.str());}


// -----
// cycle length
// -----

TEST(PFDFixture, cycle_length1) {
    const int c = pfd_cycle_length(1);
    ASSERT_EQ(1, c);}


TEST(PFDFixture, cycle_length2) {
    const int c = pfd_cycle_length(5);
    ASSERT_EQ(6, c);}

TEST(PFDFixture, cycle_length3) {
    const int c = pfd_cycle_length(10);
    ASSERT_EQ(7, c);}


TEST(PFDFixture, cycle_length4) {
    const int c = pfd_cycle_length(704);
    ASSERT_EQ(21, c);}

// -----
// max cycle length
// -----

TEST(PFDFixture, max_cl1) {
    const int m = pfd_maxcl(1, 10);
    ASSERT_EQ(20, m);}


TEST(PFDFixture, max_cl2) {
    const int m = pfd_maxcl(100, 200);
    ASSERT_EQ(125, m);}


TEST(PFDFixture, max_cl3) {
    const int m = pfd_maxcl(201, 210);
    ASSERT_EQ(89, m);}


TEST(PFDFixture, max_cl4) {
    const int m = pfd_maxcl(900, 1000);
    ASSERT_EQ(174, m);}


TEST(PFDFixture, max_cl5) {
    const int m = pfd_maxcl(1, 1);
    ASSERT_EQ(1, m);}


TEST(PFDFixture, max_cl6) {
    const int m = pfd_maxcl(10, 11);
    ASSERT_EQ(15, m);}


TEST(PFDFixture, max_cl7) {
    const int m = pfd_maxcl(1, 2);
    ASSERT_EQ(2, m);}
*/
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