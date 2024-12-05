#include "lib/algorithm.hpp"

#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include <tuple>
#include <vector>
#include <list>
#include <string>

struct IsEven {
    bool operator()(int i) const {
        return i % 2 == 0;
    }
};

struct ConcatOnlySmallStringsOperator {
    std::string operator()(const std::string& init, const std::string& cur) {
        if (cur.length() > 10) {
            return init;
        }
        return init + cur;
    }
};

TEST(FIND, FOUND) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_EQ(ohtuzh::find(v.begin(), v.end(), 3), v.begin() + 2);
}

TEST(FIND, NOT_FOUND) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_EQ(ohtuzh::find(v.begin(), v.end(), 6), v.end());
}

TEST(FIND_IF, FOUND) {
    std::vector<int> v = {1, 2, 3};
    ASSERT_EQ(ohtuzh::find_if(v.begin(), v.end(), IsEven{}), v.begin() + 1);
}

TEST(FIND_IF, NOT_FOUND) {
    std::vector<int> v = {1, 3, 5};
    ASSERT_EQ(ohtuzh::find_if(v.begin(), v.end(), IsEven{}), v.end());
}

TEST(ACCUMULATE, EMPTY) {
    std::vector<int> v;
    const int kInitValue = 25;
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), kInitValue), kInitValue);
}

TEST(ACCUMULATE, SUM_NUMBERS) {
    std::vector<int> v = {1, 2, 3};
    const int kInitValue = 0;
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), kInitValue), kInitValue + 1 + 2 + 3);
}

TEST(ACCUMULATE, CONCAT_ONLY_SMALL_STRINGS) {
    std::vector<std::string> v = {
        "small1",
        "hugehugehugehugehuge",
        "hugehugehugehugehuge",
        "small2",
        "small3",
        "hugehugehugehugehuge",
        "hugehugehugehugehuge"
    };
    const std::string kInitString = "init";
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), kInitString, ConcatOnlySmallStringsOperator{}), kInitString + "small1small2small3");
}

class AccumulateIntTest : public ::testing::TestWithParam<std::tuple<std::vector<int>, int, int>> {};

TEST_P(AccumulateIntTest, SimpleTest) {
    const std::vector<int>& container = std::get<0>(GetParam());
    int init = std::get<1>(GetParam());
    int result = std::get<2>(GetParam());
    ASSERT_EQ(ohtuzh::accumulate(container.begin(), container.end(), init), result);
}

INSTANTIATE_TEST_SUITE_P(
    ACCUMULATE_SIMPLE,
    AccumulateIntTest,
    ::testing::Values(
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, 0, 15),
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, 10, 25),
        std::make_tuple(std::vector<int>{1, -1, 1, -1, 1}, -1, 0)
    )
);

class AccumulateStringTest : public ::testing::TestWithParam<std::tuple<std::vector<std::string>, std::string, std::string>> {};

TEST_P(AccumulateStringTest, SimpleTest) {
    const std::vector<std::string>& container = std::get<0>(GetParam());
    std::string init = std::get<1>(GetParam());
    std::string result = std::get<2>(GetParam());
    ASSERT_EQ(ohtuzh::accumulate(container.begin(), container.end(), init), result);
}

INSTANTIATE_TEST_SUITE_P(
    ACCUMULATE_SIMPLE,
    AccumulateStringTest,
    ::testing::Values(
        std::make_tuple(std::vector<std::string>{"Hello", ", world!"}, "", "Hello, world!"),
        std::make_tuple(std::vector<std::string>{"Hello", ", world!", " Qwe."}, "", "Hello, world! Qwe.")
    )
);

// Via template:
template<typename T>
using AccumulateAnyTestParams = std::vector<std::tuple<std::vector<T>, T, T>>;

const std::tuple<AccumulateAnyTestParams<int>, AccumulateAnyTestParams<std::string>> AllAccumulateAnyTestParams = {
    {
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, 0, 15),
        std::make_tuple(std::vector<int>{1, 2, 3, 4, 5}, 10, 25),
        std::make_tuple(std::vector<int>{1, -1, 1, -1, 1}, -1, 0)
    },
    {
        std::make_tuple(std::vector<std::string>{"Hello", ", world!"}, "", "Hello, world!"),
        std::make_tuple(std::vector<std::string>{"Hello", ", world!", " Qwe."}, "", "Hello, world! Qwe.")
    }
};
using AccumulateAnyTestTypes = ::testing::Types<int, std::string>;

template<typename T>
class AccumulateAnyTest : public ::testing::Test {
public:
    AccumulateAnyTest() : params(std::get<AccumulateAnyTestParams<T>>(AllAccumulateAnyTestParams)) {}
protected:
    AccumulateAnyTestParams<T> params;
};

TYPED_TEST_SUITE(AccumulateAnyTest, AccumulateAnyTestTypes);

TYPED_TEST(AccumulateAnyTest, CommonAccumulate) {
    for (const auto& [container, init, expected]: this->params) {
        const auto actual = ohtuzh::accumulate(container.begin(), container.end(), init);
        ASSERT_EQ(actual, expected) << actual << " != " << expected;
    }
}
