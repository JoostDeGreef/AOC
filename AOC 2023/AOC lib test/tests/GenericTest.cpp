
#include "AOC.h"
#include "gtest/gtest.h"

using namespace testing;
using namespace AOC;

class GenericTest : public Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(GenericTest, Reverse)
{
    EXPECT_STREQ("4321", Reverse<std::string>("1234").c_str());
    EXPECT_STREQ("34", Reverse<std::vector<std::string>>({ "12","34" }).front().c_str());
}

TEST_F(GenericTest, ForAll)
{
    std::vector<int> input = { 0, 1, 2, 42 };
    auto res = ForAll(input, [](int i) { return i; });

    EXPECT_EQ(input, res);
}

TEST_F(GenericTest, Grid)
{
    Grid<int> g(42);
    g[Pos(1,2)] = 1;

    EXPECT_EQ(42, g(-1,0));
    EXPECT_EQ(1, g(1, 2));
}
