#pragma once

template<typename T>
class TRef {
public:
    TRef() : Counter_(0) {}
    TRef(const TRef&) : Counter_(0) {}

    void operator=(const TRef&) {
    }

    void Ref() {
        ++Counter_;
    }

    void Unref() {
        --Counter_;
        if (Counter_ == 0) {
            delete static_cast<T*>(this);
        }
    }
private:
    size_t Counter_;
};

template<typename T>
class TIntrusivePtrViaMethods {
public:
    using TPointer = T*;

    TIntrusivePtrViaMethods(TPointer ptr)
        : Ptr_(ptr)
    {
        Ptr_->Ref();
    }

    ~TIntrusivePtrViaMethods() {
        Ptr_->Unref();
    }

private:
    TPointer Ptr_;
};
