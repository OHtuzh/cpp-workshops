#pragma once

template<typename T>
class TRAII {
public:
    TRAII(const T& action)
        : Action_(action) {}

    ~TRAII() {
        Action_();
    }

private:
    T Action_;
};

#define CAT(X, Y) CAT_I(X, Y)
#define CAT_I(X, Y) X##Y

#define DEFER TRAII CAT(Raii, __LINE__) = [&]()
