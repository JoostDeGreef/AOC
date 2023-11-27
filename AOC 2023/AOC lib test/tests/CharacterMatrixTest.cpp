
#include "AOC.h"
#include "gtest/gtest.h"

using namespace testing;

class CharacterMatrixTest : public Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    std::string filename = "../AOC lib test/tests/CharacterMatrixTest.txt";
};

TEST_F(CharacterMatrixTest, GetChar)
{
    CharacterMatrix cm(TextFile(filename), 1, 2);

    EXPECT_EQ('7', cm.GetChar(2, 1));
}

