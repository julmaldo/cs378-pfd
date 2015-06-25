//Irvin Gonzalez

// --------
// includes
// --------

#include <iostream> //cout, endl
#include <sstream> //istringstream, ostringstream
#include <string> //string
#include <utility> //pair

#include "gtest/gtest.h"

#include "PFD.h"


// -------
// TestPFD
// -------


// ------
// create
// ------

TEST(PFD, create_1) {
	string r("3 2 1 5\n");
	
	std::vector<int> v (5, 0);
	std::vector<std::list<int> > m(5, std::list<int>());
	
	bool ass = PFD_create(r, m, v);
	
	ASSERT_EQ( ass, true); }
TEST(PFD, create_2) {
	string r("3 2 1 5\n");

	std::vector<int> v (5, 0);
	std::vector<std::list<int> > m(5, std::list<int>());

	bool ass = PFD_create(r, m, v);
	
	ASSERT_EQ(v[2], 2);
	ASSERT_EQ(v[0], 0); }

TEST(PFD, create_3) {
	string r("3 2 1 5\n");

	std::vector<int> v (5, 0);
	std::vector<std::list<int> > m(5, std::list<int>());

	PFD_create(r, m, v);

	ASSERT_EQ(m[0].front(), 3);
	ASSERT_EQ(m[4].front(), 3); }
TEST(PFD, create_4) {
	string r1("3 2 1 5\n");
	string r2("2 2 5 3\n");

	std::vector<int> v (5, 0);
	std::vector<std::list<int> > m(5, std::list<int>());

	PFD_create(r1, m, v);
	PFD_create(r2, m, v);

	ASSERT_EQ(m[0].front(), 3);
	ASSERT_EQ(m[4].front(), 3);
	ASSERT_EQ(m[4].back(), 2); }

// ----
// eval
// ----

TEST(PFD, eval_1) {
	std::vector<int> v(5, 0);
	v[2] = 2;

	std::vector<std::list<int> > m(5, std::list<int>());
	m[0].push_back(3);
	m[4].push_back(3);

	std::vector<int> o = PFD_eval(m, v);

	ASSERT_EQ(o[0], 1);
	ASSERT_EQ(o[1], 2);
	ASSERT_EQ(o[2], 4);
	ASSERT_EQ(o[3], 5);
	ASSERT_EQ(o[4], 3); }

TEST(PFD, eval_2) {
	std::vector<int> v(5, 0);
	v[2] = 2;
	v[1] = 2;

	std::vector<std::list<int> > m(5, std::list<int>());
	m[0].push_back(3);
	m[4].push_back(3);
	m[4].push_back(2);
	m[2].push_back(2);

	std::vector<int> o = PFD_eval(m, v);

	ASSERT_EQ(o[0], 1);
	ASSERT_EQ(o[1], 4);
	ASSERT_EQ(o[2], 5);
	ASSERT_EQ(o[3], 3);
	ASSERT_EQ(o[4], 2); }

TEST(PFD, eval_3) {
	std::vector<int> v(5, 0);
	v[2] = 2;
	v[1] = 2;
	v[3] = 1;

	std::vector<std::list<int> > m(5, std::list<int>());
	m[0].push_back(3);
	m[4].push_back(3);
	m[4].push_back(2);
	m[2].push_back(2);
	m[2].push_back(4);

	std::vector<int> o = PFD_eval(m, v);

	ASSERT_EQ(o[0], 1);
	ASSERT_EQ(o[1], 5);
	ASSERT_EQ(o[2], 3);
	ASSERT_EQ(o[3], 2);
	ASSERT_EQ(o[4], 4); }

TEST(PFD, eval_4) {
	std::vector<int> v(5, 0);
	v[2] = 2;
	v[1] = 2;
	v[3] = 1;
	v[4] = 1;

	std::vector<std::list<int> > m(5, std::list<int>());
	m[0].push_back(3);
	m[4].push_back(3);
	m[4].push_back(2);
	m[2].push_back(2);
	m[2].push_back(4);
	m[0].push_back(5);

	std::vector<int> o = PFD_eval(m, v);

	ASSERT_EQ(o[0], 1);
	ASSERT_EQ(o[1], 5);
	ASSERT_EQ(o[2], 3);
	ASSERT_EQ(o[3], 2);
	ASSERT_EQ(o[4], 4); }

// -----
// print
// -----

TEST(PFD, print_1) {
	std::vector<int> nothing(1, 0);
	
	std::ostringstream w;
	PFD_print(w, nothing);

	ASSERT_EQ("0\n", w.str()); }

TEST(PFD, print_2) {
	std::vector<int> o(5, 0);
	o[0] = 1;
	o[1] = 5;
	o[2] = 3;
	o[3] = 2;
	o[4] = 4;
	
	std::ostringstream w;
	PFD_print(w, o);

	ASSERT_EQ("1 5 3 2 4\n", w.str()); }

// -----
// solve
// -----

TEST(PFD, solve_1) {
	std::istringstream r("5 1\n3 2 1 5\n");
	std::ostringstream w;
	PFD_solve(r, w);
	ASSERT_EQ("1 2 4 5 3\n", w.str()); }

TEST(PFD, solve_2) {
	std::istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
	std::ostringstream w;
	PFD_solve(r, w);
	ASSERT_EQ("1 5 3 2 4\n", w.str()); }



 

