#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include <list>

#include "gtest/gtest.h"

#include "PFD.h"
#include "PFD.c++"
using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
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
    
    PFD_eval (final_order, num_tasks, graph, edge_count, no_predecessors);
    
    ASSERT_EQ (final_order.at(0), 1);
    ASSERT_EQ (final_order.at(1), 5);
    ASSERT_EQ (final_order.at(2), 3);
    ASSERT_EQ (final_order.at(3), 2);
    ASSERT_EQ (final_order.at(4), 4);
}
