#include <jeydia_lib/jeydia_lib.hpp>
#include <gtest/gtest.h>
#include <cstdlib>

TEST(jeydia_lib_tests, basic_test)
{
    ASSERT_EQ(module_name(), "jeydia_lib");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
