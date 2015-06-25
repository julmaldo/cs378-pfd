// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringstream, ostringstream
#include <string>   // string
#include <utility>  // pair


#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -------
// TestPFD
// -------

// ----
// read
// ----

TEST(PFDFixture, read_1)
{
    string s("1  100\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(1, p.first);
    ASSERT_EQ(100, p.second);
}

TEST(PFDFixture, read_2)
{
    string s("1000       1\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(1000, p.first);
    ASSERT_EQ(1, p.second);
}

TEST(PFDFixture, read_3)
{
    string s("   -10      -10\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(-10, p.first);
    ASSERT_EQ(-10, p.second);
}

// -----------
// build_graph
// -----------

TEST(PFDFixture, build_graph_1)
{
    vector<list<int> > graph (6);
    string line = "3 2 1 5\n";
    pfd_build_graph (graph, 3, 2, line);
    ASSERT_EQ(graph.at(1).front(), 3);
    ASSERT_EQ(graph.at(5).back(), 3);
}

TEST(PFDFixture, build_graph_2)
{
    vector<list<int> > graph (6);
    string line = "4 1 3\n";
    pfd_build_graph (graph, 4, 1, line);
    ASSERT_EQ(graph.at(3).front(), 4);
}

TEST(PFDFixture, build_graph_3)
{
    vector<list<int> > graph (6);
    string line = "1 3 3 4 5\n";
    pfd_build_graph (graph, 1, 3, line);
    ASSERT_EQ(graph.at(3).front(), 1);
    ASSERT_EQ(graph.at(4).back(), 1);
    ASSERT_EQ(graph.at(5).back(), 1);
}

// ----
// eval
// ----

TEST(PFDFixture, eval_1)
{
    int num_tasks = 5;
    priority_queue<int, vector<int>, greater<int> > no_predecessors;
    vector<int> final_order;
    
    vector<list<int> > graph;
    graph.push_back({});
    graph.push_back({3, 5});
    graph.push_back({});
    graph.push_back({4, 2});
    graph.push_back({});
    graph.push_back({3, 2});

    vector<int> edge_count;
    edge_count.push_back(0);
    edge_count.push_back(0);
    edge_count.push_back(2);
    edge_count.push_back(2);
    edge_count.push_back(1);
    edge_count.push_back(1);
    
    pfd_eval (final_order, num_tasks, graph, edge_count, no_predecessors);
    
    ASSERT_EQ (final_order.at(0), 1);
    ASSERT_EQ (final_order.at(1), 5);
    ASSERT_EQ (final_order.at(2), 3);
    ASSERT_EQ (final_order.at(3), 2);
    ASSERT_EQ (final_order.at(4), 4);
}

TEST(PFDFixture, eval_2)
{
    int num_tasks = 4;
    priority_queue<int, vector<int>, greater<int> > no_predecessors;
    vector<int> final_order;
    
    vector<list<int> > graph;
    graph.push_back({});
    graph.push_back({});
    graph.push_back({});
    graph.push_back({1});
    graph.push_back({1});

    vector<int> edge_count;
    edge_count.push_back(0);
    edge_count.push_back(2);
    edge_count.push_back(0);
    edge_count.push_back(0);
    edge_count.push_back(0);
    
    pfd_eval (final_order, num_tasks, graph, edge_count, no_predecessors);
    
    ASSERT_EQ (final_order.at(0), 2);
    ASSERT_EQ (final_order.at(1), 3);
    ASSERT_EQ (final_order.at(2), 4);
    ASSERT_EQ (final_order.at(3), 1);
}

TEST(PFDFixture, eval_3)
{
    int num_tasks = 4;
    priority_queue<int, vector<int>, greater<int> > no_predecessors;
    vector<int> final_order;
    
    vector<list<int> > graph;
    graph.push_back({});
    graph.push_back({});
    graph.push_back({});
    graph.push_back({2});
    graph.push_back({1});
    graph.push_back({});

    vector<int> edge_count;
    edge_count.push_back(0);
    edge_count.push_back(1);
    edge_count.push_back(1);
    edge_count.push_back(0);
    edge_count.push_back(0);
    
    pfd_eval (final_order, num_tasks, graph, edge_count, no_predecessors);
    
    ASSERT_EQ (final_order.at(0), 3);
    ASSERT_EQ (final_order.at(1), 2);
    ASSERT_EQ (final_order.at(2), 4);
    ASSERT_EQ (final_order.at(3), 1);
}

// -----
// print
// -----

TEST(PFDFixture, print_1)
{
    ostringstream w;
    vector<int> final_order (4, 100);
    pfd_print(w, final_order);
    ASSERT_EQ("100 100 100 100", w.str());
}

TEST(PFDFixture, print_2)
{
    ostringstream w;
    vector<int> final_order (1, 10);
    pfd_print(w, final_order);
    ASSERT_EQ("10", w.str());
}

TEST(PFDFixture, print_3)
{
    ostringstream w;
    vector<int> final_order (3, 0);
    pfd_print(w, final_order);
    ASSERT_EQ("0 0 0", w.str());
}

// -----
// solve
// -----

TEST(PFDFixture, solve_1)
{
    istringstream r("4 2\n1 1 4\n2 1 3\n");
    ostringstream w;
    pfd_solve (r, w);
    ASSERT_EQ("3 2 4 1", w.str());
}

TEST(PFDFixture, solve_2)
{
    istringstream r("4 1\n1 2 3 4\n");
    ostringstream w;
    pfd_solve (r, w);
    ASSERT_EQ("2 3 4 1", w.str());
}

TEST(PFDFixture, solve_3)
{
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    pfd_solve (r, w);
    ASSERT_EQ("1 5 3 2 4", w.str());
}