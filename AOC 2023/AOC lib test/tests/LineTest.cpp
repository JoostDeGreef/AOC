
#include "AOC.h"
#include "gtest/gtest.h"

using namespace testing;

class LineTest : public Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    std::string filename = "../AOC lib test/tests/LineTest.txt";
};

TEST_F(LineTest, GetLines)
{
    auto line = TextFile(filename).GetLines().at(2);
    auto word = line.GetWords().at(1);
    EXPECT_STREQ("iep", word.c_str());
}


