#pragma once

template<typename T>
void intrusive_ptr_add_ref(T* p);

template<typename T>
void intrusive_ptr_release(T * p);

template<typename T>
class TIntrusivePtr {
public:
    using TPointer = T*;

    TIntrusivePtr(TPointer ptr)
        : Ptr_(ptr)
    {
        intrusive_ptr_add_ref(Ptr_);
    }

    ~TIntrusivePtr() {
        intrusive_ptr_release(Ptr_);
    }

private:
    TPointer Ptr_;
};
