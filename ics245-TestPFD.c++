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

TEST(PFDFixture, update2) {
    ASSERT_EQ(pfd_update_tasks_list(1), 1);}

TEST(PFDFixture, update3) {
    ASSERT_EQ(pfd_update_tasks_list(5), 5);}
    
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