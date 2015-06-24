// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include <queue>

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
    string s("1 10\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(PFDFixture, read2) {
    string s("0 12345\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ( 0, p.first);
    ASSERT_EQ(12345, p.second);}

TEST(PFDFixture, read3) {
    string s("-10 789\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ( -10, p.first);
    ASSERT_EQ(789, p.second);}

// -----
// read rule
// -----

vector<int> adj(25);
vector<int> dep(5);

TEST(PFDFixture, read_rule1) {
    /* Asserting that task 3 has a dependency count of 2.
       Asserting that row 3, column 1 and 5 have a value
       of 1 in the adjacency matrix which indicates jobs 
       its dependent on. */
    string s("3 2 1 5");
    pfd_read_rule(s, adj, dep, 5);
    ASSERT_EQ(2, dep[3-1]);
    ASSERT_EQ(1, adj[10]);
    ASSERT_EQ(1, adj[14]);}

TEST(PFDFixture, read_rule2) {
    string s("5 1 1");
    pfd_read_rule(s, adj, dep, 5);
    ASSERT_EQ(1, dep[5-1]);
    ASSERT_EQ(1, adj[20]);}

TEST(PFDFixture, read_rule3) {
    string s("2 2 5 3");
    pfd_read_rule(s, adj, dep, 5);
    ASSERT_EQ(2, dep[2-1]);
    ASSERT_EQ(1, adj[7]);
    ASSERT_EQ(1, adj[9]);}

// -----
// priority queue
// -----

priority_queue<int, vector<int>, greater<int>> pq;
vector<int> dep2(5);

TEST(PFDFixture, update_pq1) {
    dep2[1] = 1;
    dep2[2] = 1;
    dep2[3] = 1;
    dep2[4] = 1;
    pfd_update_priority_queue(pq, dep2, 5);
    ASSERT_EQ( 1, pq.top());
    ASSERT_EQ(-1, dep2[1-1]);
    pq.pop();}

TEST(PFDFixture, update_pq2) {
    dep2[3] = 0;
    dep2[1] = 0;
    pfd_update_priority_queue(pq, dep2, 5);
    ASSERT_EQ( 2, pq.top());
    ASSERT_EQ(-1, dep2[2-1]);
    ASSERT_EQ(-1, dep2[4-1]);
    pq.pop();
    ASSERT_EQ( 4, pq.top());
    pq.pop();}

TEST(PFDFixture, update_pq3) {
    pfd_update_priority_queue(pq, dep2, 5);
    ASSERT_EQ(true, pq.empty());}

// -----
// schedule
// -----

vector<int> adj2(9);

TEST(PFDFixture, schedule_task1) {
    adj2[5] = 1;
    adj2[6] = 1;
    adj2[8] = 1;
    dep2[0] = 0;
    dep2[1] = 1;
    dep2[2] = 2;
    pfd_schedule_task(adj2, dep2, 1, 3);
    ASSERT_EQ(0, adj2[6]);
    ASSERT_EQ(1, dep2[2]);}

// -----
// solve
// -----

TEST(PFDFixture, solve) {
    istringstream r("5 4\n2 1 1\n3 1 2\n4 1 3\n5 1 4\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2 3 4 5 \n", w.str());}

TEST(PFDFixture, solve2) {
    istringstream r("5 4\n1 4 2 3 4 5\n2 3 4 5 3\n3 2 4 5\n 4 1 5\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("5 4 3 2 1 \n", w.str());}

TEST(PFDFixture, solve3) {
    istringstream r("10 1\n1 9 2 3 4 5 6 7 8 9 10\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("2 3 4 5 6 7 8 9 10 1 \n", w.str());}

TEST(PFDFixture, solve4) {
    istringstream r("3 1\n1 2 2 3\n2 1 3\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 2 1 \n", w.str());}

TEST(PFDFixture, solve5) {
    istringstream r("3 1\n1 2 3 2\n2 1 3\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 2 1 \n", w.str());}


    