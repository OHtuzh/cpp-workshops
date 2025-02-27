#pragma once

template<typename T>
class TIntrusivePtrRefUnref {
public:
    using TPointer = T*;

    TIntrusivePtrRefUnref(TPointer ptr)
        : Ptr_(ptr)
    {
        Ptr_->Ref();
    }

    TIntrusivePtrRefUnref(const TIntrusivePtrRefUnref& other)
        : TIntrusivePtrRefUnref(other.Ptr_)
    {
    }

    TIntrusivePtrRefUnref& operator=(const TIntrusivePtrRefUnref& other) {
        if (this == &other) {
            return *this;
        }
        Ptr_->Unref();
        Ptr_ = other.Ptr_;
        Ptr_->Ref();
        return *this;
    }

    TIntrusivePtrRefUnref& operator=(TIntrusivePtrRefUnref&&) = delete;
    TIntrusivePtrRefUnref(TIntrusivePtrRefUnref&&) = delete;

    ~TIntrusivePtrRefUnref() {
        Ptr_->Unref();
    }

private:
    TPointer Ptr_;
};
