// --------------------------------
// projects/pfd/TestPFD.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>   // vector
#include <list>     // list

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read_first
// ----

TEST(PFDFixture, read_first) {
    string s = "5 4\n";
    const pair<int, int> p = pfd_read_first(s);
    ASSERT_EQ( 5, p.first);
    ASSERT_EQ(4, p.second);
	}

// ----
// read
// ----

TEST(PFDFixture, read_1) {
    string s = "3 2 1 5\n";
    std::vector<int> p = pfd_read(s);
    ASSERT_EQ( 3, p[0]);
    ASSERT_EQ( 1, p[1]);
    ASSERT_EQ( 5, p[2]);
    }

TEST(PFDFixture, read_2) {
  string s = "1 3 2 2 5\n";
  std::vector<int> p = pfd_read(s);
  ASSERT_EQ( 1, p[0]);
  ASSERT_EQ( 2, p[1]);
  ASSERT_EQ( 2, p[2]);
  ASSERT_EQ( 5, p[3]);
}



// ----
// make_lists
// ----

TEST(PFDFixture, make_lists_1) {
    std::vector<list<int>> lists = make_lists(5);
    ASSERT_EQ( 5, lists.size());
	}

TEST(PFDFixture, make_lists_2) {
    std::vector<list<int>> lists = make_lists(2);
    ASSERT_EQ( 0, lists[0].size());
    ASSERT_EQ( 0, lists[1].size());
    }

// ----
// set_lists
// ----

TEST(PFDFixture, set_lists_1) {
    make_lists(5);
    std::vector<list<int>> lists = set_list({ 3, 1, 5 });
    ASSERT_EQ( 1, lists[0].size());
    ASSERT_EQ( 1, lists[4].size());
	}

TEST(PFDFixture, set_lists_2) {
    make_lists(5);
    auto lists = set_list({ 3, 1, 5 });
    ASSERT_EQ( 3, lists[0].front());
    ASSERT_EQ( 3, lists[4].front());
	}

TEST(PFDFixture, set_lists_3) {
    make_lists(5);
    set_list({ 3, 1, 5 });
    auto lists = set_list({ 4, 1, 3 });
    ASSERT_EQ( 2, lists[0].size());
    ASSERT_EQ( 1, lists[2].size());
    ASSERT_EQ( 1, lists[4].size());
    }

TEST(PFDFixture, set_lists_4) {
    make_lists(5);
    set_list({ 3, 1, 5 });
    auto lists = set_list({ 4, 1, 3 });
    auto iter1 = lists[0].begin();
    ASSERT_EQ( 3, *(iter1++));
    ASSERT_EQ( 4, *(iter1++));
    ASSERT_EQ( 3, lists[4].front());
    ASSERT_EQ( 4, lists[2].front());
    }

// ----
// make_graph
// ----

// test having correct graph values from 1 rule input
TEST(PFDFixture, make_graph_1) {
    istringstream r("5 1\n3 2 1 5\n");
    auto lists = make_graph(r);
    ASSERT_EQ( 5, lists.size());
    ASSERT_EQ( 3, lists[0].front());
    ASSERT_EQ( 3, lists[4].front());
	}

// test having correct number of successors for each task from sample input
TEST(PFDFixture, make_graph_2) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
    auto lists = make_graph(r);
    ASSERT_EQ( 5, lists.size());
    ASSERT_EQ( 2, lists[0].size());
    ASSERT_EQ( 0, lists[1].size());
    ASSERT_EQ( 2, lists[2].size());
    ASSERT_EQ( 0, lists[3].size());
    ASSERT_EQ( 2, lists[4].size());
    }

// test having correct successors for each task from sample input
TEST(PFDFixture, make_graph_3) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
    auto lists = make_graph(r);
    // 1 before 3, 5
    auto iter = lists[0].begin();
    ASSERT_EQ( 3, *(iter++));
    ASSERT_EQ( 5, *(iter++));
    // 2 before none
    // 3 before 2, 4
    iter = lists[2].begin();
    ASSERT_EQ( 2, *(iter++));
    ASSERT_EQ( 4, *(iter++));
    // 4 before none
    // 5 before 3, 2
    iter = lists[4].begin();
    ASSERT_EQ( 3, *(iter++));
    ASSERT_EQ( 2, *(iter++));
    }

// ----
// task_independent
// ----

// test finding a solution on a very simple graph
TEST(PFDFixture, task_independent_1) {
    // Test graph:
    // 1 before 2
    vector<list<int>> graph = {{2}, {}};
    ASSERT_EQ(true, task_independent(graph, 1));
    ASSERT_EQ(false, task_independent(graph, 2));
    }

TEST(PFDFixture, task_independent_2) {
    // Test graph:
    // no rules
    vector<list<int>> graph = {{}, {}};
    ASSERT_EQ(true, task_independent(graph, 1));
    ASSERT_EQ(true, task_independent(graph, 2));
    }

TEST(PFDFixture, task_independent_3) {
    // Test graph:
    // Sample Graph
    vector<list<int>> graph = {{3, 5}, {}, {2, 4}, {}, {3, 2}};
    ASSERT_EQ(true, task_independent(graph, 1));
    ASSERT_EQ(false, task_independent(graph, 2));
    ASSERT_EQ(false, task_independent(graph, 3));
    ASSERT_EQ(false, task_independent(graph, 4));
    ASSERT_EQ(false, task_independent(graph, 5));
    }

// ----
// eval
// ----

// test finding a solution on a very simple graph
TEST(PFDFixture, eval_1) {
    // Test graph:
    // 1 before 2
    vector<list<int>> graph = {{2}, {}};
    vector<int> solution = pfd_eval(graph);
    ASSERT_EQ(2, solution.size());
    auto iter = solution.begin();
    ASSERT_EQ(1, *(iter++));
    ASSERT_EQ(2, *(iter++));
	}

// test finding a solution on sample graph
TEST(PFDFixture, eval_2) {
    // Test graph: Sample Graph
    // 1 before 3, 5
    // 3 before 2, 4
    // 5 before 3, 2
    vector<list<int>> graph = {{3, 5}, {}, {2, 4}, {}, {3, 2}};
    vector<int> solution = pfd_eval(graph);
    ASSERT_EQ(5, solution.size());
    auto iter = solution.begin();
    ASSERT_EQ(1, *(iter++));
    ASSERT_EQ(5, *(iter++));
    ASSERT_EQ(3, *(iter++));
    ASSERT_EQ(2, *(iter++));
    ASSERT_EQ(4, *(iter++));
}

// -----
// print
// -----

TEST(PFDFixture, print) {
    ostringstream w;
    pfd_print(w, {1, 5, 3, 2, 4}, 5);
    ASSERT_EQ("1 5 3 2 4\n", w.str());
	}

// -----
// solve
// -----

TEST(PFDFixture, solve_1) {
    istringstream r("2 1\n2 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 2\n", w.str());
	}

TEST(PFDFixture, solve_2) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4\n", w.str());
    }

TEST(PFDFixture, solve_3) {
  istringstream r("4 2\n1 1 4\n2 1 3\n");
  ostringstream w;
  pfd_solve(r, w);
  ASSERT_EQ("3 2 4 1\n", w.str());
}

TEST(PFDFixture, solve_4) {
  istringstream r("6 4\n3 2 4 1\n6 2 1 3\n1 1 5\n4 2 2 5\n");
  ostringstream w;
  pfd_solve(r, w);
  ASSERT_EQ("2 5 1 4 3 6\n", w.str());
}

TEST(PFDFixture, solve_5) {
  istringstream r("4 2\n3 1 2\n4 3 1 3 2\n");
  ostringstream w;
  pfd_solve(r, w);
  ASSERT_EQ("1 2 3 4\n", w.str());
}

TEST(PFDFixture, solve_6) {
  istringstream r("1 0\n");
  ostringstream w;
  pfd_solve(r, w);
  ASSERT_EQ("1\n", w.str());
}

TEST(PFDFixture, solve_7) {
  istringstream r("3 2\n1 1 2\n3 1 2\n");
  ostringstream w;
  pfd_solve(r, w);
  ASSERT_EQ("2 1 3\n", w.str());
}

TEST(PFDFixture, solve_8) {
  istringstream r("5 4\n2 1 4\n1 1 3\n4 1 3\n3 1 5\n");
  ostringstream w;
  pfd_solve(r, w);
  ASSERT_EQ("5 3 1 4 2\n", w.str());
}

TEST(PFDFixture, solve_9) {
  istringstream r("3 2\n1 2 3 2\n2 1 3\n");
  ostringstream w;
  pfd_solve(r, w);
  ASSERT_EQ("3 2 1\n", w.str());
}



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



% cat TestPFD.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestPFD
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from PFD
[ RUN      ] PFD.read
[       OK ] PFD.read (31 ms)
[ RUN      ] PFD.eval_1
[       OK ] PFD.eval_1 (5 ms)
[ RUN      ] PFD.eval_2
[       OK ] PFD.eval_2 (3 ms)
[ RUN      ] PFD.eval_3
[       OK ] PFD.eval_3 (3 ms)
[ RUN      ] PFD.eval_4
[       OK ] PFD.eval_4 (3 ms)
[ RUN      ] PFD.print
[       OK ] PFD.print (17 ms)
[ RUN      ] PFD.solve
[       OK ] PFD.solve (10 ms)
[----------] 7 tests from PFD (88 ms total)

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
File 'PFD.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'PFD.c++.gcov'
...
File 'TestPFD.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestPFD.c++.gcov'
...
*/
