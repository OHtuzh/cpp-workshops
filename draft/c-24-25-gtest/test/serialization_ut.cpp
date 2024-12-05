#include "lib/serialization.hpp"

#include <sstream>

#include <gtest/gtest.h>

TEST(SERIALIZE, SINGLE_DATA) {
    ohtuzh::data data("name", {1, 2, 3, 4, 5}, ohtuzh::state::kOk);
    std::stringstream ss;
    data.serialize(ss);
    ASSERT_EQ(
        ss.str(),
        "name|1,2,3,4,5,|OK\n"
    );
}

TEST(DESERIALIZE, SINGLE_DATA) {
    ohtuzh::data real;
    std::stringstream ss("name|1,2,3,4,5,|OK\n");
    real.deserialize(ss);

    ohtuzh::data expected("name", {1, 2, 3, 4, 5}, ohtuzh::state::kOk);
    ASSERT_EQ(real, expected);
}

class MyTestSuite : public ::testing::TestWithParam<std::tuple<std::string, std::vector<int32_t>, ohtuzh::state>> {};

TEST_P(MyTestSuite, Combine) {
    const auto& [name, numbers, state] = GetParam();
    ohtuzh::data test_data(name, numbers, state);

    std::stringstream ss;
    test_data.serialize(ss);

    ohtuzh::data deserialized_data;
    deserialized_data.deserialize(ss);

    ASSERT_EQ(test_data, deserialized_data);
}

INSTANTIATE_TEST_SUITE_P(
    CombinedGroup,
    MyTestSuite,
    testing::Combine(
        testing::Values("", "abc", "abcdefghqwe"),
        testing::Values(std::vector<int32_t>{}, std::vector<int32_t>{1, 2, 3}, std::vector<int32_t>{1, 2, 3, 4, 5, 6, 7, 8}),
        testing::Values(ohtuzh::state::kBad, ohtuzh::state::kOk)
    )
);
