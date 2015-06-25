// --------------------------------
// TestPFD.c++
// Justin Salazar
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <vector>

#include "gtest/gtest.h"
#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
// ----

TEST(PFDFixture, read1) {
    istringstream s ("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n 5 1 1\n");
    vector<vector<int> > r = pfd_read(s);
    vector<vector<int> > q(6, vector<int> (6,0));
    q[2][0] = 2;
    q[3][0] = 2;
    q[4][0] = 1;
    q[5][0] = 1;
    q[3][1] = 1;
    q[5][1] = 1;
    q[2][3] = 1;
    q[4][3] = 1;
    q[2][5] = 1;
    q[3][5] = 1;

    ASSERT_EQ(q, r);}

TEST(PFDFixture, read2) {
    istringstream s ("3 1\n1 1 2\n");
    vector<vector<int> > r = pfd_read(s);
    vector<vector<int> > q(4, vector<int> (4,0));
    q[1][0] = 1;
    q[1][2] = 1;

    ASSERT_EQ(q, r);}


TEST(PFDFixture, read3) {
    istringstream s ("4 2\n2 2 3 4\n1 1 3\n");
    vector<vector<int> > r = pfd_read(s);
    vector<vector<int> > q(5, vector<int> (5,0));
    q[1][0] = 1;
    q[1][3] = 1;
    q[2][0] = 2;
    q[2][3] = 1;
    q[2][4] = 1;

    ASSERT_EQ(q, r);}

// ----
// eval
// ----

TEST(PFDFixture, eval1) {
    vector<vector<int> > q(6, vector<int> (6,0));
    q[2][0] = 2;
    q[3][0] = 2;
    q[4][0] = 1;
    q[5][0] = 1;
    q[3][1] = 1;
    q[5][1] = 1;
    q[2][3] = 1;
    q[4][3] = 1;
    q[2][5] = 1;
    q[3][5] = 1;

    vector<int> a = pfd_eval(q);
    int myresult[] = {1, 5, 3, 2, 4};
    vector<int> r (myresult, myresult + sizeof(myresult)/ sizeof(int) );

    ASSERT_EQ(a, r);}


TEST(PFDFixture, eval2) {
   vector<vector<int> > q(4, vector<int> (4,0));
    q[1][0] = 1;
    q[1][2] = 1;

    vector<int> a = pfd_eval(q);
    int myresult[] = {2, 1, 3};
    vector<int> r (myresult, myresult + sizeof(myresult)/ sizeof(int) );

    ASSERT_EQ(a, r);}


TEST(PFDFixture, eval3) {
     vector<vector<int> > q(5, vector<int> (5,0));
    q[1][0] = 1;
    q[1][3] = 1;
    q[2][0] = 2;
    q[2][3] = 1;
    q[2][4] = 1;
    vector<int> a = pfd_eval(q);
    int myresult[] = {3, 1, 4, 2};
    vector<int> r (myresult, myresult + sizeof(myresult)/ sizeof(int) );

    ASSERT_EQ(a, r);}
// ----
// print
// ----

TEST(PFDFixture, print1) {
    ostringstream w;
    int myresult[] = {1, 5, 3, 2, 4};
    vector<int> r (myresult, myresult + sizeof(myresult)/ sizeof(int) );

    pfd_print(r, w);

    ASSERT_EQ("1 5 3 2 4", w.str());}

TEST(PFDFixture, print2) {
    ostringstream w;
    int myresult[] = {2, 1, 3};
    vector<int> r (myresult, myresult + sizeof(myresult)/ sizeof(int) );

    pfd_print(r, w);

    ASSERT_EQ("2 1 3", w.str());}

TEST(PFDFixture, print3) {
    ostringstream w;
    int myresult[] = {4, 6, 2, 1, 5};
    vector<int> r (myresult, myresult + sizeof(myresult)/ sizeof(int) );

    pfd_print(r, w);

    ASSERT_EQ("4 6 2 1 5", w.str());}


// ----
// solve
// ----

TEST(PFDFixture, solve1) {
    istringstream s ("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n 5 1 1\n");
    ostringstream w;
    pfd_solve(s, w);

    ASSERT_EQ("1 5 3 2 4", w.str());}

TEST(PFDFixture, solve2) {
    istringstream s ("3 1\n1 1 2\n");
    ostringstream w;
    pfd_solve(s, w);

    ASSERT_EQ("2 1 3", w.str());}

TEST(PFDFixture, solve3) {
    istringstream s ("4 2\n2 2 3 4\n1 1 3\n");
    ostringstream w;
    pfd_solve(s, w);

    ASSERT_EQ("3 1 4 2", w.str());}