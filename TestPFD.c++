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
