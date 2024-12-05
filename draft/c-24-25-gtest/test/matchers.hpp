#include <gmock/gmock.h>

MATCHER_P(MyElementsAre, container, "") {
    if (arg.size() != container.size()) {
        return false;
    }
    auto arg_it = arg.begin();
    auto container_it = container.begin();
    for (; container_it != container.end(); ++arg_it, ++container_it) {
        if (*arg_it != *container_it) {
            return false;
        }
    }
    return true;
}
