// --------------------------
// Matt Hauglund
// mlh2544
// --------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

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

// -------------------
// read_dimensions
// -------------------

TEST(PFDFixture, read_dimensions_1) {
    string s("5 4\n");
    const pair<int, int> p = pfd_read_dimensions(s);
    ASSERT_EQ(5, p.first);
    ASSERT_EQ(4, p.second);
}

TEST(PFDFixture, read_dimensions_2) {
    string s("15 29\n");
    const pair<int, int> p = pfd_read_dimensions(s);
    ASSERT_EQ(15, p.first);
    ASSERT_EQ(29, p.second);
}

TEST(PFDFixture, read_dimensions_3) {
    string s("84 255\n");
    const pair<int, int> p = pfd_read_dimensions(s);
    ASSERT_EQ(84, p.first);
    ASSERT_EQ(255, p.second);
}

// -------------
// read_rule
// -------------

TEST(PFDFixture, read_rule_1) {
    string s("3 2 1 5\n");
    vector<list<int>> g(4, list<int>(2));
    pfd_read_rule(s, g);

    list<int>::iterator it = g[2].begin();
    ASSERT_EQ(1, *it);
    it++;
    ASSERT_EQ(5, *it);
}

TEST(PFDFixture, read_rule_2) {
    string s("8 5 1 2 3 4 5\n");
    vector<list<int>> g(12, list<int>(5));
    pfd_read_rule(s, g);

    list<int>::iterator it = g[7].begin();
    ASSERT_EQ(1, *it);
    it++;
    ASSERT_EQ(2, *it);
    it++;
    ASSERT_EQ(3, *it);
    it++;
    ASSERT_EQ(4, *it);
    it++;
    ASSERT_EQ(5, *it);
}

TEST(PFDFixture, read_rule_3) {
    string s("1 1 2\n");
    vector<list<int>> g(2, list<int>(1));
    pfd_read_rule(s, g);

    list<int>::iterator it = g[0].begin();
    ASSERT_EQ(2, *it);
}

// ------------
// eval
// ------------

TEST(PFDFixture, eval_1) {
    vector<list<int>> g(6);
    int rule1[] = {0};
    int rule2[] = {5, 3};
    int rule3[] = {1, 5};
    int rule4[] = {3};
    int rule5[] = {1};
    g[0] = list<int>(1); copy (rule1, rule1 + 1, g[0].begin());
    g[1] = list<int>(2); copy (rule2, rule2 + 2, g[1].begin());
    g[2] = list<int>(2); copy (rule3, rule3 + 2, g[2].begin());
    g[3] = list<int>(1); copy (rule4, rule4 + 1, g[3].begin());
    g[4] = list<int>(1); copy (rule5, rule5 + 1, g[4].begin());
    list<int> s;
    pfd_eval(g, s);

    list<int>::iterator it = s.begin();
    ASSERT_EQ(1, *it);
    it++;
    ASSERT_EQ(5, *it);
    it++;
    ASSERT_EQ(3, *it);
    it++;
    ASSERT_EQ(2, *it);
    it++;
    ASSERT_EQ(4, *it);
}

TEST(PFDFixture, eval_2) {
    vector<list<int>> g(4);
    int rule1[] = {2};
    int rule2[] = {0};
    int rule3[] = {0};
    g[0] = list<int>(1); copy (rule1, rule1 + 1, g[0].begin());
    g[1] = list<int>(1); copy (rule2, rule2 + 1, g[1].begin());
    g[2] = list<int>(1); copy (rule3, rule3 + 1, g[2].begin());
    list<int> s;
    pfd_eval(g, s);

    list<int>::iterator it = s.begin();
    ASSERT_EQ(2, *it);
    it++;
    ASSERT_EQ(1, *it);
    it++;
    ASSERT_EQ(3, *it);
}

TEST(PFDFixture, eval_3) {
    vector<list<int>> g(5);
    int rule1[] = {3};
    int rule2[] = {1};
    int rule3[] = {0};
    int rule4[] = {0};
    g[0] = list<int>(1); copy (rule1, rule1 + 1, g[0].begin());
    g[1] = list<int>(1); copy (rule2, rule2 + 1, g[1].begin());
    g[2] = list<int>(1); copy (rule3, rule3 + 1, g[2].begin());
    g[3] = list<int>(1); copy (rule4, rule4 + 1, g[3].begin());
    list<int> s;
    pfd_eval(g, s);

    list<int>::iterator it = s.begin();
    ASSERT_EQ(3, *it);
    it++;
    ASSERT_EQ(1, *it);
    it++;
    ASSERT_EQ(2, *it);
    it++;
    ASSERT_EQ(4, *it);
}

// -------------
// print
// -------------

TEST(PFDFixture, print_1) {
    ostringstream w;

    int s[] = {1, 5, 3, 2, 4};
    list<int> sorted(s, s + sizeof(s) / sizeof(int));

    pfd_print(w, sorted);
    ASSERT_EQ("1 5 3 2 4 \n", w.str());
}

TEST(PFDFixture, print_2) {
    ostringstream w;

    int s[] = {2, 1, 3};
    list<int> sorted(s, s + sizeof(s) / sizeof(int));

    pfd_print(w, sorted);
    ASSERT_EQ("2 1 3 \n", w.str());
}

TEST(PFDFixture, print_3) {
    ostringstream w;

    int s[] = {3, 4, 1, 2};
    list<int> sorted(s, s + sizeof(s) / sizeof(int));

    pfd_print(w, sorted);
    ASSERT_EQ("3 4 1 2 \n", w.str());
}

// -------------
// solve
// -------------

TEST(PFDFixture, solve_1) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4 \n", w.str());
}

TEST(PFDFixture, solve_2) {
    istringstream r("3 2\n1 1 2\n3 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("2 1 3 \n", w.str());
}

TEST(PFDFixture, solve_3) {
    istringstream r("4 2\n1 1 3\n2 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("3 1 2 4 \n", w.str());
}
