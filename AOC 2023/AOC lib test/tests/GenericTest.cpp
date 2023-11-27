
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


