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

// TODO: cartesian product | ::testing::Combine
