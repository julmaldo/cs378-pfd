
#include <iostream> 
#include <sstream>  
#include <string>  
#include <utility>  

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------

// ----
// read
// ----

TEST(PFDFixture, pfd_read1) {
    string s("5 4\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ( 5, p.first);
    ASSERT_EQ(4, p.second);}
TEST(PFDFixture, read2) {
    string s("8 6\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(8, p.first);
    ASSERT_EQ(6, p.second);}
TEST(PFDFixture, read3) {
    string s("20 10\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(20, p.first);
    ASSERT_EQ(10, p.second);}
TEST(PFDFixture, read4) {
    string s("20 30\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(20, p.first);
    ASSERT_EQ(30, p.second);}
TEST(PFDFixture, read5) {
    string s("40 39\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(40, p.first);
    ASSERT_EQ(39, p.second);}
TEST(PFDFixture, read6) {
    string s("29 28\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(29, p.first);
    ASSERT_EQ(28, p.second);}
TEST(PFDFixture, read7) {
    string s("28 27\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(28, p.first);
    ASSERT_EQ(27, p.second);}
TEST(PFDFixture, read8) {
    string s("27 26\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(27, p.first);
    ASSERT_EQ(26, p.second);}
TEST(PFDFixture, read9) {
    string s("26 25\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(26, p.first);
    ASSERT_EQ(25, p.second);}
TEST(PFDFixture, read10) {
    string s("25 24\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(25, p.first);
    ASSERT_EQ(24, p.second);}
TEST(PFDFixture, read11) {
    string s("23 22\n");
    const pair<int, int> p = pfd_read(s);
    ASSERT_EQ(23, p.first);
    ASSERT_EQ(22, p.second);}

// ----
// eval
// ----


TEST(PFDFixture, pfd_eval) {
    ostringstream w;
    string r = "5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n 5 1 1\n";
    istringstream test1;
    test1.str(r);
    pfd_eval((pfd_build_graph(test1,w)), w);
    ASSERT_EQ("1 5 3 2 4 \n", w.str());}

TEST(PFDFixture, pfd_eval1) {
    ostringstream w;
    string r = "4 0\n";
    istringstream test2;
    test2.str(r);
    pfd_eval((pfd_build_graph(test2,w)), w);
    ASSERT_EQ("1 2 3 4 \n", w.str());}

TEST(PFDFixture, pfd_eval2) {
    ostringstream w;
    string r = "4 2\n1 1 4\n2 1 3\n";
    istringstream test3;
    test3.str(r);
    pfd_eval((pfd_build_graph(test3,w)), w);
    ASSERT_EQ("3 2 4 1 \n", w.str());
}

TEST(PFDFixture, pfd_eval3) {
    ostringstream w;
    string r = "50 49\n1 1 50\n2 1 1\n3 1 1\n4 1 2\n5 1 2\n6 1 2\n7 1 2\n8 1 3\n9 1 3\n10 1 3\n11 1 3\n12 1 11\n13 1 11\n14 1 11\n15 1 11\n16 1 10\n17 1 10\n18 1 10\n20 1 9\n21 1 9\n22 1 9\n23 1 8\n24 1 8\n25 1 8\n26 1 4\n27 1 5\n28 1 6\n29 1 7\n30 1 8\n31 1 9\n32 1 10\n33 1 11\n34 1 12\n35 1 13\n36 1 4\n37 1 5\n38 1 6\n39 1 7\n40 1 8\n41 1 9\n42 1 9\n42 1 10\n43 1 11\n44 1 12\n45 1 13\n46 1 1\n47 1 1\n48 1 2\n49 1 2\n";
    istringstream test4;
    test4.str(r);
    pfd_eval((pfd_build_graph(test4,w)), w);
    ASSERT_EQ("19 50 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 \n", w.str());
}


