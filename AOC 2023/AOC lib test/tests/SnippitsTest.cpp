#include "gtest/gtest.h"

#include "AOC.h"

using namespace testing;
using namespace std;
using namespace AOC;

class SnippitsTest : public Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(SnippitsTest, Reverse)
{
    std::vector<std::string> v = {"a","C","B","d"};
    EXPECT_EQ(Reverse(v), (std::vector<std::string>{"d", "B", "C", "a"}));
}

TEST_F(SnippitsTest, Sort)
{
    std::vector<std::string> v = { "a","C","B","d" };
    EXPECT_EQ(Sort(v), (std::vector<std::string>{"B", "C", "a", "d"}));
    EXPECT_EQ(CaseInsensitiveSort(v), (std::vector<std::string>{"a", "B", "C", "d"}));
}

