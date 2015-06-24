
#include <iostream> 
#include <sstream>  
#include <string>  
#include <utility>  

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
// ----

TEST(PFDFixture, pfd_read1) {
    string s("5 4\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ( 5, p.first);
    ASSERT_EQ(4, p.second);}
TEST(PFDFixture, read2) {
    string s("8 6\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(8, p.first);
    ASSERT_EQ(6, p.second);}
TEST(PFDFixture, read3) {
    string s("20 10\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(20, p.first);
    ASSERT_EQ(10, p.second);}

// ----
// eval
// ----


TEST(PFDFixture, pfd_eval) {
    ostringstream w;
    string r = "5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n 5 1 1\n";
    istringstream test1;
    test1.str(r);
    pfd_eval((pfd_build_graph(test1,w)), w);
    ASSERT_EQ("1 5 3 2 4 \n", w.str());}

TEST(PFDFixture, pfd_eval1) {
    ostringstream w;
    string r = "4 0\n";
    istringstream test2;
    test2.str(r);
    pfd_eval((pfd_build_graph(test2,w)), w);
    ASSERT_EQ("1 2 3 4 \n", w.str());}

TEST(PFDFixture, pfd_eval2) {
    ostringstream w;
    string r = "4 2\n1 1 4\n2 1 3\n";
    istringstream test3;
    test3.str(r);
    pfd_eval((pfd_build_graph(test3,w)), w);
    ASSERT_EQ("3 2 4 1 \n", w.str());
}


// -----
// pfd_buld_graph
// -----

TEST(PFDFixture, pfd_build_graph) {
    ostringstream w;
    string r = "5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n 5 1 1\n";
    istringstream test1;
    test1.str(r);
    pfd_build_graph(test1,w);
    pfd_print_graph(5,w);
    ASSERT_EQ(w.str(),"{11111}\n{00101}\n{00000}\n{01010}\n{00000}\n{01100}\n");}

TEST(PFDFixture, pfd_build_graph1) {
    cleararray();
    ostringstream x;
    string r = "4 \0\n";
    istringstream test2;
    test2.str(r);
    pfd_build_graph(test2,x);
    pfd_print_graph(4,x);
    ASSERT_EQ("{1111}\n{0000}\n{0000}\n{0000}\n{0000}\n", x.str());}
TEST(PFDFixture, pfd_build_graph2) {
    cleararray();
    ostringstream y;
    string r = "4 2\n1 1 4\n2 1 3\n";
    istringstream test3;
    test3.str(r);
    pfd_build_graph(test3,y);
    pfd_print_graph(4,y);
    ASSERT_EQ("{1111}\n{0000}\n{0000}\n{0100}\n{1000}\n", y.str());}


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
