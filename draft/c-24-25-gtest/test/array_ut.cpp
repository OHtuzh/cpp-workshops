#include "lib/array.hpp"

#include "matchers.hpp"

#include <gtest/gtest.h>

TEST(ARRAY_INIT, INIT_SIZE) {
    ohtuzh::array<int, 5> array;
    ASSERT_EQ(array.size(), 5);
}

TEST(ARRAY_INIT, INIT_VIA_IL) {
    ohtuzh::array<int, 5> array = {1, 2, 3, 4, 5};
    ASSERT_THAT(array, MyElementsAre(std::vector<int>{1, 2, 3, 4, 5}));
    /*
        ASSERT_EQ(array[0], 1);
        ASSERT_EQ(array[1], 2);
        ASSERT_EQ(array[2], 3);
        ASSERT_EQ(array[3], 4);
        ASSERT_EQ(array[4], 5);
        
        or

        ASSERT_THAT(array, ::testing::ElementsAre(1, 2, 3, 4, 5));
    */
}

TEST(ARRAY_INIT, INIT_WITH_EXCEPTION) {
    using array_type = ::ohtuzh::array<int, 3>;
    ASSERT_THROW(array_type({1, 2, 3, 4, 5}), std::runtime_error);
    /*
        так не компилится, вот почему:
        https://stackoverflow.com/questions/38030048/too-many-arguments-provided-to-function-like-macro-invocation
        ASSERT_ANY_THROW(::ohtuzh::array<int, 3>({1, 2, 3, 4, 5}));
    */
}

TEST(ARRAY_ACCESS, ACCESS_VIA_BRACKETS) {
    ohtuzh::array<int, 5> array = {1, 2, 3, 4, 5};
    array[3] = 10;
    ASSERT_EQ(array[3], 10);
}

TEST(ARRAY_ACCESS, ACCESS_VIA_AT) {
    ohtuzh::array<int, 5> array = {1, 2, 3, 4, 5};
    array.at(3) = 10;
    ASSERT_EQ(array.at(3), 10);
}

#define MY_ASSERT_ANY_THROW(expr)   \
    try {                           \
        expr;                       \
        ASSERT_TRUE(false);          \
    } catch(...) {                  \
        ASSERT_TRUE(true);         \
    }                               \

TEST(ARRAY_ACCESS, ACCESS_VIA_AT_EXCEPTION) {
    ohtuzh::array<int, 5> array = {1, 2, 3, 4, 5};
    MY_ASSERT_ANY_THROW(array.at(6));
}
