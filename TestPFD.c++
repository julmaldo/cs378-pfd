
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include <list>

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read

TEST(PFDFixture, solve_1) {
    istringstream r("1 1\n1 0\n");
    ostringstream w;
    solve_PFD(r, w);
    ASSERT_EQ("1 ", w.str());
    }

TEST(PFDFixture, solve_2) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1\n");
    ostringstream w;
    solve_PFD(r, w);
    ASSERT_EQ("1 5 3 2 4 ", w.str());
    }
TEST(PFDFixture, solve_3) {
    istringstream r("4 2\n1 1 4\n2 1 3\n");
    ostringstream w;
    solve_PFD(r, w);
    ASSERT_EQ("3 2 4 1 ", w.str());
    //clear_adj(4);
}
TEST(PFDFixture, solve_4) {
    istringstream r("4 1\n1 2 3 4\n");
    ostringstream w;
    solve_PFD(r, w);
    ASSERT_EQ("2 3 4 1 ", w.str());
    //clear_adj(4);}
}
TEST(PFDFixture, solve_5) {
    istringstream r("8 5\n1 2 4 5\n2 1 4\n3 2 5 8\n4 2 6 7\n5 1 7\n");
    ostringstream w;
    solve_PFD(r, w);
   ASSERT_EQ("6 7 4 2 5 1 8 3 ", w.str());
}
TEST(PFDFixture, solve_6) 
{
    istringstream r("5 0\n");
    ostringstream w;
    solve_PFD(r, w);
    ASSERT_EQ("1 2 3 4 5 ", w.str());
}