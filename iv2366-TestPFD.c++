#include "gtest/gtest.h"

#include "PFD.h"

TEST(PFDFixture, ParseTaskHeader_should_parse_sphere_input)
{
    string s("5 4\n");

    auto p = ParseTaskHeader(s);
    
    ASSERT_EQ(5, p.first);
    ASSERT_EQ(4, p.second);
}

TEST(PFDFixture, ParseTaskHeader_should_only_parse_first_two_numbers)
{
	string s("5 4 1\n");

	auto p = ParseTaskHeader(s);

	ASSERT_EQ(5, p.first);
	ASSERT_EQ(4, p.second);
}

TEST(PFDFixture, ParseTaskHeader_should_parse_same_numbers)
{
	string s("5 5\n");

	auto p = ParseTaskHeader(s);

	ASSERT_EQ(5, p.first);
	ASSERT_EQ(5, p.second);
}

TEST(PFDFixture, ParseRule_should_parse_zero_rules)
{
	string s("3 0\n");

	auto v = ParseRule(s);

	ASSERT_EQ(2, v.size());
	ASSERT_EQ(3, v[0]);
	ASSERT_EQ(0, v[1]);
}

TEST(PFDFixture, ParseRule_should_parse_one_rule)
{
	string s("3 1 1\n");

	auto v = ParseRule(s);

	ASSERT_EQ(3, v.size());
	ASSERT_EQ(3, v[0]);
	ASSERT_EQ(1, v[1]);
	ASSERT_EQ(1, v[2]);
}

TEST(PFDFixture, ParseRule_should_parse_two_rules)
{
	string s("3 2 1 2\n");

	auto v = ParseRule(s);

	ASSERT_EQ(4, v.size());
	ASSERT_EQ(3, v[0]);
	ASSERT_EQ(2, v[1]);
	ASSERT_EQ(1, v[2]);
	ASSERT_EQ(2, v[3]);
}

TEST(PFDFixture, PrintTasksToStream_should_print_no_tasks)
{
	vector<int> v;
	ostringstream oss;

	PrintTasksToStream(v, oss);

	ASSERT_EQ("\n", oss.str());
}

TEST(PFDFixture, PrintTasksToStream_should_print_one_task)
{
	vector<int> v = {1};
	ostringstream oss;

	PrintTasksToStream(v, oss);

	ASSERT_EQ("1\n", oss.str());
}

TEST(PFDFixture, PrintTasksToStream_should_print_two_tasks)
{
	vector<int> v = {1, 2};
	ostringstream oss;

	PrintTasksToStream(v, oss);

	ASSERT_EQ("1 2\n", oss.str());
}

TEST(PFDFixture, PopulateDependencies_should_populate_no_dependencies)
{
	istringstream iss("");

	auto dependencyLists = PopulateDependencies(iss, 5, 0);

	ASSERT_EQ(5, dependencyLists.size());
}

TEST(PFDFixture, PopulateDependencies_should_populate_with_missing_rules)
{
	istringstream iss("");

	auto dependencyLists = PopulateDependencies(iss, 2, 0);

	ASSERT_EQ(2, dependencyLists.size());
	ASSERT_TRUE(dependencyLists[0].empty());
	ASSERT_TRUE(dependencyLists[1].empty());
}

TEST(PFDFixture, PopulateDependencies_should_populate_with_one_rule)
{
	istringstream iss("2 1 1");

	auto dependencyLists = PopulateDependencies(iss, 2, 1);

	ASSERT_EQ(2, dependencyLists.size());
	ASSERT_TRUE(dependencyLists[0].empty());
	ASSERT_TRUE(dependencyLists[1].count(1));
}

TEST(PFDFixture, PopulateDependencies_should_populate_with_two_rules)
{
	istringstream iss("2 1 1\n 3 2 1 2");

	auto dependencyLists = PopulateDependencies(iss, 3, 2);

	ASSERT_EQ(3, dependencyLists.size());
	ASSERT_TRUE(dependencyLists[0].empty());
	ASSERT_TRUE(dependencyLists[1].count(1));
	ASSERT_TRUE(dependencyLists[2].count(1));
	ASSERT_TRUE(dependencyLists[2].count(2));
}

TEST(PFDFixture, FindTasksWithNoDependencies_should_return_empty_when_all_have_dependencies)
{
	vector<unordered_set<int>> v = {{1}, {1}};

	auto mh = FindTasksWithNoDependencies(v);

	ASSERT_EQ(0, mh.size());
}

TEST(PFDFixture, FindTasksWithNoDependencies_should_return_single_task_with_no_dependency)
{
	vector<unordered_set<int>> v = {{1}};
	unordered_set<int> two;
	v.push_back(two);

	auto mh = FindTasksWithNoDependencies(v);

	ASSERT_EQ(1, mh.size());
	ASSERT_EQ(2, mh.top());
}

TEST(PFDFixture, FindTasksWithNoDependencies_should_return_all_tasks_with_no_dependency)
{
	vector<unordered_set<int>> v;
	unordered_set<int> one;
	unordered_set<int> two;
	v.push_back(one);
	v.push_back(two);

	auto mh = FindTasksWithNoDependencies(v);

	ASSERT_EQ(2, mh.size());
	ASSERT_EQ(1, mh.top());
	mh.pop();
	ASSERT_EQ(2, mh.top());
}

TEST(PFDFixture, CompleteTasks_should_return_empty_when_all_tasks_have_dependency)
{
	vector<unordered_set<int>> v = {{1}, {1}};

	auto completedTasks = CompleteTasks(v);

	ASSERT_EQ(0, completedTasks.size());
}

TEST(PFDFixture, CompleteTasks_should_return_all_tasks_when_no_dependency)
{
	vector<unordered_set<int>> v;
	unordered_set<int> one;
	unordered_set<int> two;
	v.push_back(one);
	v.push_back(two);

	auto completedTasks = CompleteTasks(v);

	ASSERT_EQ(2, completedTasks.size());
	ASSERT_EQ(1, completedTasks[0]);
	ASSERT_EQ(2, completedTasks[1]);
}

TEST(PFDFixture, CompleteTasks_should_return_ordered_tasks_from_sphere)
{
	unordered_set<int> noDependencies;
	vector<unordered_set<int>> v = {noDependencies, {5, 3}, {1, 5}, {3}, {1}};

	auto completedTasks = CompleteTasks(v);

	ASSERT_EQ(5, completedTasks.size());
	ASSERT_EQ(1, completedTasks[0]);
	ASSERT_EQ(5, completedTasks[1]);
	ASSERT_EQ(3, completedTasks[2]);
	ASSERT_EQ(2, completedTasks[3]);
	ASSERT_EQ(4, completedTasks[4]);
}

TEST(PFDFixture, PfdSolve_should_solve_sphere)
{
	string s("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
	istringstream iss(s);
	ostringstream oss;

	PfdSolve(iss, oss);

	ASSERT_EQ("1 5 3 2 4\n", oss.str());
}

TEST(PFDFixture, PfdSolve_should_solve_empty_case)
{
	string s("5 0\n");
	istringstream iss(s);
	ostringstream oss;

	PfdSolve(iss, oss);

	ASSERT_EQ("1 2 3 4 5\n", oss.str());
}