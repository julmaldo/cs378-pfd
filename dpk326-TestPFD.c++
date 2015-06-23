// ------------------
// cs378-pfd/PFD.c++
// Copyright (C) 2015
// David Peter Ko
// Josh Gutierrez
// ------------------

// -------
// Defines
// -------

// --------
// Includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

//priority_queue<int, vector<int>, greater<int> > pq = {6, 2};
//priority_queue<int, vector<int>, greater<int> > pq = {14, 24, 39};

// -------
// TestPFD
// -------

// ---------
// pfd_solve
// ---------
TEST(PFDFixture, solve1) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n 5 1 1\n");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4", w.str());}


// -----------
// print_queue
// -----------
TEST(PFDFixture, print1){
	priority_queue<int, vector<int>, greater<int> > pq;

	int i = 5;
	pq.push(i);

	ostringstream w;
	print_queue(w, pq);

	ASSERT_EQ("5\n", w.str());
}

TEST(PFDFixture, print2){
	priority_queue<int, vector<int>, greater<int> > pq;

	int i = 5;
	pq.push(i);

	ostringstream w;
	print_queue(w, pq);

	ASSERT_EQ("5\n", w.str());
}

TEST(PFDFixture, print3){
	priority_queue<int, vector<int>, greater<int> > pq;

	int i = 7;
	pq.push(i);

	ostringstream w;
	print_queue(w, pq);

	ASSERT_EQ("7\n", w.str());
}

TEST(PFDFixture, print4){
	priority_queue<int, vector<int>, greater<int> > pq;

	int i = 10;
	pq.push(i);

	ostringstream w;
	print_queue(w, pq);

	ASSERT_EQ("10\n", w.str());
}


TEST(PFDFixture, print5){
	priority_queue<int, vector<int>, greater<int> > pq;

	int i = 14;
	pq.push(i);
	i = 6; 
	pq.push(i);
	i = 9;
	pq.push(i);

	ostringstream w;
	print_queue(w, pq);

	ASSERT_EQ("6\n", w.str());
}

// ------------
// print_matrix
// ------------
TEST(PFDFixture,printmatrix1){
	ostringstream w;
	vector<vector<int> > testmatrix(2, vector<int>(2)); 

	for(int i = 0; i < 2; ++i){

		for(int j = 0; j < 2; ++j){

			testmatrix[i][j] = 1;
		}
	}

	print_matrix(w, testmatrix);

	ASSERT_EQ("(1)(1)\n(1)(1)\n", w.str());
}

TEST(PFDFixture,printmatrix2){
	ostringstream w;
	vector<vector<int> > testmatrix(3, vector<int>(3)); 

	for(int i = 0; i < 3; ++i){

		for(int j = 0; j < 3; ++j){

			testmatrix[i][j] = 2;
		}
	}

	print_matrix(w, testmatrix);

	ASSERT_EQ("(2)(2)(2)\n(2)(2)(2)\n(2)(2)(2)\n", w.str());
}

TEST(PFDFixture,printmatrix3){
	ostringstream w;
	vector<vector<int> > testmatrix(4, vector<int>(4)); 

	for(int i = 0; i < 4; ++i){

		for(int j = 0; j < 4; ++j){

			testmatrix[i][j] = 3;
		}
	}

	print_matrix(w, testmatrix);

	ASSERT_EQ("(3)(3)(3)(3)\n(3)(3)(3)(3)\n(3)(3)(3)(3)\n(3)(3)(3)(3)\n", w.str());
}



 // ------------------------------
 // Expected Output of TestPFD.c++
 // ------------------------------




