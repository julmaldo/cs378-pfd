//Chris Martin
//Rachel Frock

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <vector>   // vector<T>

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
// ----

TEST(PFDFixture, read) 
{
    string s1("5 4\n");
    string s2("3 2 1 5\n");
    string s3("2 2 5 3\n");
    string s4("4 1 3\n");
    string s5("5 1 1\n");
    vector<int> line1 = pfd_read(s1);
    vector<int> rule1 = pfd_read(s2);
    vector<int> rule2 = pfd_read(s3);
    vector<int> rule3 = pfd_read(s4);
    vector<int> rule4 = pfd_read(s5); 
    ASSERT_EQ(5, line1[0]);
    ASSERT_EQ(4, line1[1]);
    ASSERT_EQ(3, rule1[0]);
    ASSERT_EQ(2, rule1[1]);
    ASSERT_EQ(1, rule1[2]);
    ASSERT_EQ(5, rule1[3]);
    ASSERT_EQ(2, rule2[0]);
    ASSERT_EQ(2, rule2[1]);
    ASSERT_EQ(5, rule2[2]);
    ASSERT_EQ(3, rule2[3]);
    ASSERT_EQ(4, rule3[0]);
    ASSERT_EQ(1, rule3[1]);
    ASSERT_EQ(3, rule3[2]);
    ASSERT_EQ(5, rule4[0]);
    ASSERT_EQ(1, rule4[1]);
    ASSERT_EQ(1, rule4[2]);
}

// ----
// eval
// ----

TEST(PFDFixture, eval_1) 
{
    const int jobs = 5;

    vector< list< int > > adj_list;

    list<int> l1;
    l1.push_back(3);
    l1.push_back(5);

    list<int> l2;

    list<int> l3;
    l3.push_back(2);
    l3.push_back(4);

    list<int> l4;

    list<int> l5;
    l5.push_back(3);
    l5.push_back(2);

    adj_list.push_back(l1);
    adj_list.push_back(l2);
    adj_list.push_back(l3);
    adj_list.push_back(l4);
    adj_list.push_back(l5);

    vector<int> pre_counts(jobs);
    pre_counts[1] = 2;
    pre_counts[2] = 2;
    pre_counts[3] = 1;
    pre_counts[4] = 1;

    vector<int> v = pfd_eval(jobs, adj_list, pre_counts);
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(5, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(2, v[3]);
    ASSERT_EQ(4, v[4]);
}

TEST(PFDFixture, eval_2) 
{
    const int jobs = 4;

    vector< list< int > > adj_list;

    list<int> l1;

    list<int> l2;

    list<int> l3;
    l3.push_back(2);

    list<int> l4;
    l4.push_back(1);

    adj_list.push_back(l1);
    adj_list.push_back(l2);
    adj_list.push_back(l3);
    adj_list.push_back(l4);

    vector<int> pre_counts(jobs);
    pre_counts[0] = 1;
    pre_counts[1] = 1;

    vector<int> v = pfd_eval(jobs, adj_list, pre_counts);
    ASSERT_EQ(3, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(4, v[2]);
    ASSERT_EQ(1, v[3]);
}

TEST(PFDFixture, eval_3) 
{
    const int jobs = 5;

    vector< list< int > > adj_list;

    list<int> l1;

    list<int> l2;

    list<int> l3;

    list<int> l4;

    list<int> l5;

    adj_list.push_back(l1);
    adj_list.push_back(l2);
    adj_list.push_back(l3);
    adj_list.push_back(l4);
    adj_list.push_back(l5);

    vector<int> pre_counts(jobs);

    vector<int> v = pfd_eval(jobs, adj_list, pre_counts);
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
    ASSERT_EQ(5, v[4]);
}

TEST(PFDFixture, eval_4) 
{
    const int jobs = 5;

    vector< list< int > > adj_list;

    list<int> l1;

    list<int> l2;
    l2.push_back(1);

    list<int> l3;
    l3.push_back(1);

    list<int> l4;
    l4.push_back(1);

    list<int> l5;
    l5.push_back(1);

    adj_list.push_back(l1);
    adj_list.push_back(l2);
    adj_list.push_back(l3);
    adj_list.push_back(l4);
    adj_list.push_back(l5);

    vector<int> pre_counts(jobs);
    pre_counts[0] = 4;

    vector<int> v = pfd_eval(jobs, adj_list, pre_counts);
    ASSERT_EQ(2, v[0]);
    ASSERT_EQ(3, v[1]);
    ASSERT_EQ(4, v[2]);
    ASSERT_EQ(5, v[3]);
    ASSERT_EQ(1, v[4]);
}

TEST(PFDFixture, eval_5) 
{
    const int jobs = 5;

    vector< list< int > > adj_list;

    list<int> l1;
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);

    list<int> l2;

    list<int> l3;

    list<int> l4;

    list<int> l5;

    adj_list.push_back(l1);
    adj_list.push_back(l2);
    adj_list.push_back(l3);
    adj_list.push_back(l4);
    adj_list.push_back(l5);

    vector<int> pre_counts(jobs);
    pre_counts[1] = 1;
    pre_counts[2] = 1;
    pre_counts[3] = 1;
    pre_counts[4] = 1;

    vector<int> v = pfd_eval(jobs, adj_list, pre_counts);
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
    ASSERT_EQ(5, v[4]);
}

// -----
// print
// -----

TEST(PFDFixture, print) 
{
    ostringstream w;
    const int jobs = 5;
    vector<int> output;
    output.push_back(1);
    output.push_back(5);
    output.push_back(3);
    output.push_back(2);
    output.push_back(4);
    pfd_print(w, output, jobs);
    ASSERT_EQ("1 5 3 2 4", w.str());
}

// -----
// solve
// -----

TEST(PFDFixture, solve_1) 
{
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4", w.str());
}

TEST(PFDFixture, solve_2) 
{
    istringstream r("4 2\n1 1 4\n2 1 3\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 2 4 1", w.str());
}

TEST(PFDFixture, solve_3) 
{
    istringstream r("5 0\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2 3 4 5", w.str());
}

TEST(PFDFixture, solve_4) 
{
    istringstream r("5 1\n1 4 2 3 4 5\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("2 3 4 5 1", w.str());
}

TEST(PFDFixture, solve_5) 
{
    istringstream r("5 4\n2 1 1\n3 1 1\n4 1 1\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2 3 4 5", w.str());
}