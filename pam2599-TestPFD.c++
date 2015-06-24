// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <deque>    // deque

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// -------
// loadLine
// -------

TEST(PFDFixture, loadLine_1) {
    PFDQueue test(5);
    deque<int> succ;

    test.loadLine("3 2 1 5");
    assert(test.dependencies[3] == 2);
    succ = {3};
    assert(succ == test.successors[1]);
    assert(succ == test.successors[5]);

    test.loadLine("2 2 5 3");
    assert(test.dependencies[2] == 2);
    succ = {2};
    assert(succ == test.successors[3]);
    succ = {3, 2};
    assert(succ == test.successors[5]);

    test.loadLine("4 1 3");
    assert(test.dependencies[4] == 1);
    succ = {2, 4};
    assert(succ == test.successors[3]);

    test.loadLine("5 1 1");
    assert(test.dependencies[5] == 1);
    succ = {3, 5};
    assert(succ == test.successors[1]);
}

TEST(PFDFixture, loadLine_2) {
    PFDQueue test(5);

    test.loadLine("2 2 5 3");
    assert(test.dependencies[2] == 2);
    deque<int> succ = {2};
    assert(succ == test.successors[5]);
    assert(succ == test.successors[3]);
}

TEST(PFDFixture, loadLine_3) {
    PFDQueue test(5);

    test.loadLine("4 1 3");
    assert(test.dependencies[4] == 1);
    deque<int> succ = {4};
    assert(succ == test.successors[3]);
}

// ----------
// PFD::solve
// ----------

TEST(PFDFixture, pfd_solve_1) {
    PFDQueue test(5);
    vector<int> ans;
    vector<int> expected;

    test.loadLine("3 2 1 5");
    expected = {1, 2, 4, 5, 3};
    test.solve(ans);
    assert(ans == expected);
}

TEST(PFDFixture, pfd_solve_2) {
    PFDQueue test(5);
    vector<int> ans;
    vector<int> expected;

    test.loadLine("3 2 1 5");
    test.loadLine("2 2 5 3");
    expected = {1, 4, 5, 3, 2};
    test.solve(ans);
    assert(ans == expected);
}

TEST(PFDFixture, pfd_solve_3) {
    PFDQueue test(5);
    vector<int> ans;
    vector<int> expected;

    test.loadLine("3 2 1 5");
    test.loadLine("2 2 5 3");
    test.loadLine("4 1 3");
    expected = {1, 5, 3, 2, 4};
    test.solve(ans);
    assert(ans == expected);
}

// ---------------
// get_tasks_rules
// ---------------
TEST(PFDFixture, get_tasks_rules_1) {
    pair<int, int> test = get_tasks_rules("5 4");
    assert(test == make_pair(5, 4));
}

TEST(PFDFixture, get_tasks_rules_2) {
    pair<int, int> test = get_tasks_rules("50 44");
    assert(test == make_pair(50, 44));
}

TEST(PFDFixture, get_tasks_rules_3) {
    pair<int, int> test = get_tasks_rules("100 99");
    assert(test == make_pair(100, 99));
}


// -----
// solve
// -----

TEST(PFDFixture, solve_1) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("1 5 3 2 4\n", w.str());
}

TEST(PFDFixture, solve_2) {
    istringstream r("4 1\n1 2 3 4\n");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("2 3 4 1\n", w.str());
}

TEST(PFDFixture, solve_3) {
    istringstream r("4 2\n1 1 4\n2 1 3\n");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("3 2 4 1\n", w.str());
}
