
#include <iostream> // cout, endl                                                           
#include <sstream>  // istringtstream, ostringstream                                        
#include <string>   // string                                                               
#include <utility>  // pair                                                                 

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;



TEST(PFDFixture, solve_1)
{
	istringstream r("5 4\n 2 3 1 5\n 2 2 5 3\n 4 1 3\n 5 1 1");
	ostringstream w; 
	solve_pfd(r, w);
	ASSERT_EQ("1 5 3 2 4", w.str());
}



TEST(PFDFixture, solve_2)
{
	istringstream r("1 0");
	ostringstream w; 
	solve_pfd(r, w);
	ASSERT_EQ("1", w.str());
}




TEST(PFDFixture, solve_3)
{
	istringstream r("10 2\n 8 1 6\n 9 3 2 4 5");
	ostringstream w; 
	solve_pfd(r, w);
	ASSERT_EQ("1 3 7 10 5 4 2 9 6 8", w.str());
}




