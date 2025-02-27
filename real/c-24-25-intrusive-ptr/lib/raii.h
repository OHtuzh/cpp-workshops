#pragma once

template<typename Func>
class TRaiiImplementation {
public:
    TRaiiImplementation(const Func& functor)
        : Functor_(functor)
    {}

    ~TRaiiImplementation() {
        Functor_();
    }

private:
    Func Functor_;
};

#define CAT(X, Y) X##Y
#define CAT_I(X, Y) X##Y

#define DEFER TRaiiImplementation CAT(raii, __LINE__) = [&]()
