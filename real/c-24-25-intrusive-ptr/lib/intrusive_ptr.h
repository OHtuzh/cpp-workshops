#pragma once

template<typename T>
void intrusive_ptr_add_ref(T* p);

template<typename T>
void intrusive_ptr_release(T* p);

template<typename T>
class TIntrusivePtr {
public:
    using TPointer = T*;

    TIntrusivePtr(TPointer ptr)
        : Ptr_(ptr)
    {
        intrusive_ptr_add_ref(Ptr_);
    }

    TIntrusivePtr(const TIntrusivePtr& other)
        : TIntrusivePtr(other.Ptr_)
    {
    }

    TIntrusivePtr& operator=(const TIntrusivePtr& other) {
        if (this == &other) {
            return *this;
        }
        intrusive_ptr_release(Ptr_);
        Ptr_ = other.Ptr_;
        intrusive_ptr_add_ref(Ptr_);
        return *this;
    }

    TIntrusivePtr& operator=(TIntrusivePtr&&) = delete;
    TIntrusivePtr(TIntrusivePtr&&) = delete;

    ~TIntrusivePtr() {
        intrusive_ptr_release(Ptr_);
    }
private:
    TPointer Ptr_;
};
