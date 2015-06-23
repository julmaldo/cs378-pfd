
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
    int arr[10100] = {};
    istringstream s("");
    //test empty should do nothing
    pfd_read(s, arr, 1);
    for(int i = 0; i < 10100; ++i){
        ASSERT_EQ(arr[i], 0);
    }
}

TEST(PFDFixture, read_2) {
    int arr[10100] = {};
    istringstream s("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    //tests to see if pred count works
    pfd_read(s, arr, 5);
    ASSERT_EQ(arr[0], 0);
    ASSERT_EQ(arr[6], 2);
    ASSERT_EQ(arr[12], 2);
    ASSERT_EQ(arr[18], 1);
    ASSERT_EQ(arr[24], 1);
}

TEST(PFDFixture, read_3) {
    int arr[10100] = {};
    istringstream s("3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    //tests to see if suc correctly stored
    pfd_read(s, arr, 5);
    ASSERT_EQ(arr[1], 3);
    ASSERT_EQ(arr[2], 5);
    ASSERT_EQ(arr[25], 3);
    ASSERT_EQ(arr[26], 2);
}

TEST(PFDFixture, read_4) {
    int arr[10100] = {};
    istringstream s("2 2 5 3\n3 2 1 5\n5 1 1\n4 1 3\n");
    //tests to see if pred count works, order should not modify
    pfd_read(s, arr, 5);
    ASSERT_EQ(arr[0], 0);
    ASSERT_EQ(arr[6], 2);
    ASSERT_EQ(arr[12], 2);
    ASSERT_EQ(arr[18], 1);
    ASSERT_EQ(arr[24], 1);
}

TEST(PFDFixture, read_5) {
    int arr[10100] = {};
    istringstream s("2 2 5 3\n3 2 1 5\n5 1 1\n4 1 3\n");
    //tests to see if suc correctly stored, order may modify
    pfd_read(s, arr, 5);
    ASSERT_EQ(arr[1], 3);
    ASSERT_EQ(arr[2], 5);
    ASSERT_EQ(arr[25], 2);
    ASSERT_EQ(arr[26], 3);
    ASSERT_EQ(arr[13], 2);
    ASSERT_EQ(arr[14], 4);
}

// ----
// eval
// ----

TEST(PFDFixture, eval_1) {
    int arr[10100] = {};
    int ans[100] = {};
    //1 task, no rules
    pfd_eval(arr, 1, ans);
    ASSERT_EQ(ans[0], 1);
}

TEST(PFDFixture, eval_2) {
    int arr[10100] = {};
    int ans[100] = {};
    //5 tasks, no rules
    pfd_eval(arr, 5, ans);
    ASSERT_EQ(ans[0], 1);
    ASSERT_EQ(ans[1], 2);
    ASSERT_EQ(ans[2], 3);
    ASSERT_EQ(ans[3], 4);
    ASSERT_EQ(ans[4], 5);
}

TEST(PFDFixture, eval_3) {
    int arr[10100] = {};
    int ans[100] = {};
    //5 tasks, with 4 rules, basic PFD
    istringstream s("2 2 5 3\n3 2 1 5\n5 1 1\n4 1 3\n");
    //tests to see if suc correctly stored, order may modify
    pfd_read(s, arr, 5);
    pfd_eval(arr, 5, ans);
    ASSERT_EQ(ans[0], 1);
    ASSERT_EQ(ans[1], 5);
    ASSERT_EQ(ans[2], 3);
    ASSERT_EQ(ans[3], 2);
    ASSERT_EQ(ans[4], 4);
}


// -----
// print
// -----

TEST(PFDFixture, print_1) {
    ostringstream w;
    int arr[100] = {1, 10, 20};
    pfd_print(w, arr);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(PFDFixture, print_2) {
    ostringstream w;
    int arr[100] = {1};
    pfd_print(w, arr);
    ASSERT_EQ("1\n", w.str());}

// -----
// solve
// -----

TEST(PFDFixture, solve_1) {
    istringstream r("5 0\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2 3 4 5\n", w.str());}

TEST(PFDFixture, solve_2) {
    istringstream r("1 0\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1\n", w.str());}

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




*/
