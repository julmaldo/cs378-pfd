#include <iostream> // cout, endl
#include <sstream>  // istringstream, ostringstream
#include <string>   // string
#include <list>     // list
#include <algorithm>// equal

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -------
// TestPFD
// -------

// ----
// read
// ----

TEST(PFDFixture, read) {
    istringstream s("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    vector<Task> tasks = pfd_read(s);
    
    ASSERT_EQ(tasks.size(), 5);
    ASSERT_EQ(tasks[2].dependencies.size(), 2);
    ASSERT_EQ(tasks[2].dependencies.front(), 1);
    ASSERT_EQ(tasks[1].dependencies.size(), 2);
    ASSERT_EQ(tasks[1].dependencies.front(), 5);
    ASSERT_EQ(tasks[3].dependencies.size(), 1);
    ASSERT_EQ(tasks[3].dependencies.front(), 3);
    ASSERT_EQ(tasks[4].dependencies.size(), 1);
    ASSERT_EQ(tasks[4].dependencies.front(), 1);
}

TEST(PFDFixture, read2) {
    istringstream s("3 1\n1 2 3 4\n");
    vector<Task> tasks = pfd_read(s);

    ASSERT_EQ(tasks.size(), 3);
    ASSERT_EQ(tasks[0].dependencies.size(), 2);
    ASSERT_EQ(tasks[0].dependencies.front(), 3);
}

TEST(PFDFixture, read3) {
    istringstream s("4 2\n2 3 1 2 4\n3 1 4\n");
    vector<Task> tasks = pfd_read(s);

    ASSERT_EQ(tasks.size(), 4);
    ASSERT_EQ(tasks[1].dependencies.size(), 3);
    ASSERT_EQ(tasks[1].dependencies.front(), 1);
    ASSERT_EQ(tasks[2].dependencies.size(), 1);
    ASSERT_EQ(tasks[2].dependencies.front(), 4);
}

// ----
// eval
// ----

TEST(PFDFixture, eval) {
    vector<Task> tasklist;
    list<int> rule;
    rule.push_back(2);
    rule.push_back(3);
    rule.push_back(4);
    tasklist.push_back(Task(1, rule));
    list<int> rule2;
    rule2.push_back(3);
    rule2.push_back(4);
    tasklist.push_back(Task(2, rule));
    tasklist.push_back(Task(3));
    tasklist.push_back(Task(4));
    list<int> result = pfd_eval(tasklist);
    list<int> comparelist;
    comparelist.push_back(1);
    comparelist.push_back(2);
    comparelist.push_back(3);
    comparelist.push_back(4);
    ASSERT_TRUE(result == comparelist);
}

TEST(PFDFixture, eval2) {
    list<int> comparelist;
    istringstream s("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    list<int> result = pfd_eval(pfd_read(s));

    comparelist.push_back(1);
    comparelist.push_back(5);
    comparelist.push_back(3);
    comparelist.push_back(2);
    comparelist.push_back(4);

    ASSERT_TRUE(result == comparelist);
}

TEST(PFDFixture, eval3) {
    list<int> comparelist;
    istringstream s("4 3\n1 2 4\n3 1 2\n2 4\n");
    list<int> result = pfd_eval(pfd_read(s));

    comparelist.push_back(2);
    comparelist.push_back(3);
    comparelist.push_back(4);
    comparelist.push_back(1);

    ASSERT_TRUE(result == comparelist);
}

// -----
// print
// -----

TEST(PFDFixture, print) {
    ostringstream w;
    list<int> printlist;
    printlist.push_back(2);
    printlist.push_back(3);
    printlist.push_back(4);
    printlist.push_back(1);
    pfd_print(w, printlist);
    ASSERT_EQ("2 3 4 1\n", w.str());
}

TEST(PFDFixture, print2) {
    ostringstream w;
    list<int> printlist;
    printlist.push_back(1);
    printlist.push_back(2);
    pfd_print(w, printlist);
    ASSERT_EQ("1 2\n", w.str());
}

TEST(PFDFixture, print3) {
    ostringstream w;
    list<int>printlist;
    printlist.push_back(5);
    printlist.push_back(4);
    printlist.push_back(3);
    printlist.push_back(2);
    printlist.push_back(1);
    pfd_print(w, printlist);
    ASSERT_EQ("5 4 3 2 1\n", w.str());
}

// -----
// solve
// -----

TEST(PFDFixture, solve) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4\n", w.str());
}

TEST(PFDFixture, solve2) {
    istringstream r("4 3\n1 2 4\n3 1 2\n2 4\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("2 3 4 1\n", w.str());
}

TEST(PFDFixture, solve3) {
    istringstream r("3 2\n1 1 3\n2 1 3\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 1 2\n", w.str());
}
