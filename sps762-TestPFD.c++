// --------
// includes
// --------

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "gtest/gtest.h"
#include "PFD.h"

using namespace std;

// --------
// Test PFD
// --------

void prepare_tasks(int n, vector<task>& tasks) {
    for (int i = 1; i <= n; ++i) {
        tasks.push_back(task(i));
    }
}

// ---------
// read_rule
// ---------

TEST(PFDFixture, read_rule_1) {
    int n = 5;
    vector<task> tasks;
    prepare_tasks(n, tasks);
    istringstream r("1 3 2 3 4");
    pfd_read_rule(r, tasks);

    ASSERT_EQ(tasks.size(), n);
    ASSERT_EQ(tasks[1].succ[0], 1);
    ASSERT_EQ(tasks[2].succ[0], 1);
    ASSERT_EQ(tasks[3].succ[0], 1);
}

TEST(PFDFixture, read_rule_2) {
    int n = 3;
    vector<task> tasks;
    prepare_tasks(n, tasks);
    istringstream r("3 2 1 3");
    pfd_read_rule(r, tasks);

    ASSERT_EQ(tasks.size(), n);
    ASSERT_EQ(tasks[0].succ[0], 3);
    ASSERT_EQ(tasks[2].succ[0], 3);
}

TEST(PFDFixture, read_rule_3) {
    int n = 5;
    vector<task> tasks;
    prepare_tasks(n, tasks);
    istringstream r("1 3 2 3 4 5");
    pfd_read_rule(r, tasks);

    ASSERT_EQ(tasks.size(), n);
    ASSERT_EQ(tasks[1].succ[0], 1);
    ASSERT_EQ(tasks[2].succ[0], 1);
    ASSERT_EQ(tasks[3].succ[0], 1);
    ASSERT_TRUE(tasks[4].succ.empty());
}

// -----
// print
// -----

TEST(PFDFixture, print_1) {
    ostringstream w;
    vector<int> order = {1, 2, 3, 4, 5};
    pfd_print(w, order);

    ASSERT_EQ(w.str(), "1 2 3 4 5");
}

TEST(PFDFixture, print_2) {
    ostringstream w;
    vector<int> order = {10000, 10, -10, -10000};
    pfd_print(w, order);

    ASSERT_EQ(w.str(), "10000 10 -10 -10000");
}

TEST(PFDFixture, print_3) {
    ostringstream w;
    vector<int> order = {1, 1, 1, 1, 1, 0, 1};
    pfd_print(w, order);

    ASSERT_EQ(w.str(), "1 1 1 1 1 0 1");
}

// ----
// sort
// ----

TEST(PFDFixture, sort_1) {
    int n = 1;
    vector<task> tasks;
    vector<int> result;
    prepare_tasks(n, tasks);
    pfd_sort(tasks, result);

    vector<int> correct = {1};
    ASSERT_EQ(result.size(), n);
    ASSERT_EQ(result, correct);
}

TEST(PFDFixture, sort_2) {
    int n = 3;
    vector<task> tasks;
    vector<int> result;
    prepare_tasks(n, tasks);
    istringstream r("1 1 2");
    pfd_read_rule(r, tasks);
    r.str("3 1 2"); r.clear();
    pfd_read_rule(r, tasks);
    pfd_sort(tasks, result);

    vector<int> correct = {2, 1, 3};
    ASSERT_EQ(result.size(), n);
    ASSERT_EQ(result, correct);
}

TEST(PFDFixture, sort_3) {
    int n = 5;
    vector<task> tasks;
    vector<int> result;
    prepare_tasks(n, tasks);
    istringstream r("3 2 1 5");
    pfd_read_rule(r, tasks);
    r.str("2 2 5 3"); r.clear();
    pfd_read_rule(r, tasks);
    r.str("4 1 3"); r.clear();
    pfd_read_rule(r, tasks);
    r.str("5 1 1"); r.clear();
    pfd_read_rule(r, tasks);
    pfd_sort(tasks, result);

    vector<int> correct = {1, 5, 3, 2, 4};
    ASSERT_EQ(result.size(), n);
    ASSERT_EQ(result, correct);
}

// -----
// solve
// -----

TEST(PFDFixture, solve_1) {
    istringstream r("1 0\n");
    ostringstream w;
    pfd_solve(r, w);

    ASSERT_EQ(w.str(), "1");
}

TEST(PFDFixture, solve_2) {
    istringstream r("3 2\n1 1 2\n3 1 2\n");
    ostringstream w;
    pfd_solve(r, w);

    ASSERT_EQ(w.str(), "2 1 3");
}

TEST(PFDFixture, solve_3) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);

    ASSERT_EQ(w.str(), "1 5 3 2 4");
}
