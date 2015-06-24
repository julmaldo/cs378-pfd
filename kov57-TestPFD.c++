#include <iostream>  // cout, endl
#include <sstream>   // istringstream, ostringstream
#include <string>    // string
#include <vector>    // vector
#include <utility>   // pair
#include <algorithm> // equal

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -------------
// addSuccessors
// -------------

TEST(PFDFixture, add_single_successor) {
	vector<vector<int>> successorList(5);
	vector<int> dependencies = {2};
	addSuccessors(successorList, 5, dependencies);
	vector<int> answer = {5}; 
	ASSERT_TRUE(equal(answer.begin(), answer.end(), successorList[1].begin()));
}

TEST(PFDFixture, add_multiple_dependencies) {
	vector<vector<int>> successorList(5);
	vector<int> dependencies = {2, 3};
	addSuccessors(successorList, 5, dependencies);
	
	vector<int> answer = {5};
	ASSERT_TRUE(equal(answer.begin(), answer.end(), successorList[1].begin()));
	ASSERT_TRUE(equal(answer.begin(), answer.end(), successorList[2].begin()));
}

TEST(PFDFixture, add_multiple_successors) {
	vector<vector<int>> successorList(5);
	vector<int> dependencies = {2};
	addSuccessors(successorList, 5, dependencies);
	addSuccessors(successorList, 4, dependencies);

	vector<int> answer = {5, 4};
	ASSERT_TRUE(equal(answer.begin(), answer.end(), successorList[1].begin()));
}

// -----------------
// pfdReadParameters
// -----------------

TEST(PFDFixture, read_sample_parameters) {
	const string s("5 4\n");
	pair<int, int> v = pfdReadParameters(s);
	ASSERT_EQ(5, v.first);
	ASSERT_EQ(4, v.second);
}

TEST(PFDFixture, read_parameters_no_rules) {
	const string s("3 0\n");
	pair<int, int> v = pfdReadParameters(s);
	ASSERT_EQ(3, v.first);
	ASSERT_EQ(0, v.second);
}

TEST(PFDFixture, read_simple_parameters) {
	const string s("3 2\n");
	pair<int, int> v = pfdReadParameters(s);
	ASSERT_EQ(3, v.first);
	ASSERT_EQ(2, v.second);
}

TEST(PFDFixture, read_large_parameters) {
	const string s("100 99\n");
	pair<int, int> v = pfdReadParameters(s);
	ASSERT_EQ(100, v.first);
	ASSERT_EQ(99, v.second);
}

// -----------
// pfdReadRule
// -----------

TEST(PFDFixture, read_simple_rule) {
	const string rule("3 2 1 2\n");
	vector<int> dependencies = {1, 2};
	pair<int, vector<int>> v = pfdReadRule(rule);
	ASSERT_EQ(3, v.first);
	ASSERT_TRUE(equal(dependencies.begin(), dependencies.end(), v.second.begin()));
}

TEST(PFDFixture, read_complex_rule) {
	const string rule("53 7 1 89 33 90 45 24 3\n");
	vector<int> dependencies = {1, 89, 33, 90, 45, 24, 3};
	pair<int, vector<int>> v = pfdReadRule(rule);
	ASSERT_EQ(53, v.first);
	ASSERT_TRUE(equal(dependencies.begin(), dependencies.end(), v.second.begin()));
}

TEST(PFDFixture, read_record_no_dependencies) {
	const string rule("3 0\n");
	vector<int> dependencies;
	pair<int, vector<int>> v = pfdReadRule(rule);
	ASSERT_EQ(3, v.first);
	ASSERT_TRUE(equal(dependencies.begin(), dependencies.end(), v.second.begin()));
}

TEST(PFDFixture, read_really_simple_rule) {
	const string rule("3 1 1\n");
	vector<int> dependencies = {1};
	pair<int, vector<int>> v = pfdReadRule(rule);
	ASSERT_EQ(3, v.first);
	ASSERT_TRUE(equal(dependencies.begin(), dependencies.end(), v.second.begin()));
}

// ----------
// pfdExecute
// ----------

TEST(PFDFixture, execute_sample_solution) {
	vector<vector<int>> successorList(5);
	successorList[0].push_back(3);
	successorList[0].push_back(5);
	successorList[2].push_back(2);	
	successorList[2].push_back(4);	
	successorList[4].push_back(3);
	successorList[4].push_back(2);
	vector<int> dependencyCount(5);
	dependencyCount[0] = 0;
	dependencyCount[1] = 2;
	dependencyCount[2] = 2;	
	dependencyCount[3] = 1;	
	dependencyCount[4] = 1;
	vector<int> orderedTasks = pfdExecute(successorList, dependencyCount);
	vector<int> answer = {1, 5, 3, 2, 4};
	vector<int> finalCount = {0, 0, 0, 0, 0};
	ASSERT_TRUE(equal(answer.begin(), answer.end(), orderedTasks.begin()));
	ASSERT_TRUE(equal(finalCount.begin(), finalCount.end(), dependencyCount.begin()));
}

TEST(PFDFixture, execute_simple_solution) {
	vector<vector<int>> successorList(3);
	successorList[0].push_back(3);
	successorList[0].push_back(2);
	successorList[1].push_back(3);
	vector<int> dependencyCount(3);
	dependencyCount[0] = 0;
	dependencyCount[1] = 1;
	dependencyCount[2] = 2;
	vector<int> orderedTasks = pfdExecute(successorList, dependencyCount);
	vector<int> answer = {1, 2, 3};
	vector<int> finalCount = {0, 0, 0};
	ASSERT_TRUE(equal(answer.begin(), answer.end(), orderedTasks.begin()));
	ASSERT_TRUE(equal(finalCount.begin(), finalCount.end(), dependencyCount.begin()));
}

TEST(PFDFixture, execute_more_than_one_task_with_no_dependencies) {
	vector<vector<int>> successorList(4);
	successorList[0].push_back(4);
	successorList[1].push_back(1);
	successorList[1].push_back(4);
	successorList[2].push_back(1);
	successorList[2].push_back(4);
	vector<int> dependencyCount(4);
	dependencyCount[0] = 2;
	dependencyCount[1] = 0;
	dependencyCount[2] = 0;
	dependencyCount[3] = 3;
	vector<int> orderedTasks = pfdExecute(successorList, dependencyCount);
	vector<int> answer = {2, 3, 1, 4};
	vector<int> finalCount = {0, 0, 0, 0};
	ASSERT_TRUE(equal(answer.begin(), answer.end(), orderedTasks.begin()));
	ASSERT_TRUE(equal(finalCount.begin(), finalCount.end(), dependencyCount.begin()));
}

TEST(PFDFixture, execute_competing_dependencies) {
	vector<vector<int>> successorList(3);
	successorList[0].push_back(3);
	successorList[0].push_back(2);
	vector<int> dependencyCount(3);
	dependencyCount[0] = 0;
	dependencyCount[1] = 1;
	dependencyCount[2] = 1;
	vector<int> orderedTasks = pfdExecute(successorList, dependencyCount);
	vector<int> answer = {1, 2, 3};
	vector<int> finalCount = {0, 0, 0};
	ASSERT_TRUE(equal(answer.begin(), answer.end(), orderedTasks.begin()));
	ASSERT_TRUE(equal(finalCount.begin(), finalCount.end(), dependencyCount.begin()));
}

// --------
// pfdWrite
// --------

TEST(PFDFixture, write_empty) {
	ostringstream w;
	vector<int> answers;
	pfdWrite(w, answers);
	ASSERT_EQ("", w.str());
}

TEST(PFDFixture, write_sample_output) {
	ostringstream w;
	vector<int> answers;
	answers.push_back(1);
	answers.push_back(5);
	answers.push_back(3);
	answers.push_back(2);
	answers.push_back(4);
	pfdWrite(w, answers);
	ASSERT_EQ("1 5 3 2 4\n", w.str());
}

TEST(PFDFixture, write_simple_output) {
	ostringstream w;
	vector<int> answers;
	answers.push_back(1);
	answers.push_back(2);
	answers.push_back(3);
	pfdWrite(w, answers);
	ASSERT_EQ("1 2 3\n", w.str());
}

TEST(PFDFixture, write_more_than_one_task_with_no_dependencies_output) {
	ostringstream w;
	vector<int> answers;
	answers.push_back(2);
	answers.push_back(3);
	answers.push_back(1);
	answers.push_back(4);
	pfdWrite(w, answers);
	ASSERT_EQ("2 3 1 4\n", w.str());
}

TEST(PFDFixture, write_competing_dependencies_output) {
	ostringstream w;
	vector<int> answers;
	answers.push_back(1);
	answers.push_back(2);
	answers.push_back(3);
	pfdWrite(w, answers);
	ASSERT_EQ("1 2 3\n", w.str());
}
// --------
// pfdSolve
// --------

TEST(PFDFixture, solve_sample_input) {
        istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
        ostringstream w;
        pfdSolve(r, w);
        ASSERT_EQ("1 5 3 2 4\n", w.str());
}

TEST(PFDFixture, solve_simple) {
        istringstream r("3 2\n3 2 2 1\n2 1 1\n");
        ostringstream w;
        pfdSolve(r, w);
        ASSERT_EQ("1 2 3\n", w.str());
}

TEST(PFDFixture, solve_more_than_one_task_with_no_dependencies) {
        istringstream r("4 2\n4 3 2 1 3\n1 2 3 2\n");
        ostringstream w;
        pfdSolve(r, w);
        ASSERT_EQ("2 3 1 4\n", w.str());
}

TEST(PFDFixture, solve_competing_dependencies) {
        istringstream r("3 2\n3 1 1\n2 1 1\n");
        ostringstream w;
        pfdSolve(r, w);
        ASSERT_EQ("1 2 3\n", w.str());
}
