
#include "AOC.h"
#include "gtest/gtest.h"

using namespace testing;

class TextFileTest : public Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    std::string filename = "../AOC lib test/tests/TextFileTest.txt";
};

TEST_F(TextFileTest, GetLines)
{
    TextFile f(filename);

    EXPECT_STREQ("1234", std::string(f.GetLines().at(1)).c_str());
}

TEST_F(TextFileTest, Count)
{
    TextFile f(filename);

    EXPECT_EQ(4, f.Count());
}

