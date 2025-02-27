#include <iostream>

#include <lib/raii.h>
#include <lib/intrusive_ptr.h>
#include <lib/intrusive_ptr_ref_unref.h>

template<typename Derived>
class TRefable {
public:
    void Ref() {
        ++RefCount_;
    }

    void Unref() {
        --RefCount_;
        if (RefCount_ == 0) {
            delete static_cast<Derived*>(this);
        }
    }

private:
    size_t RefCount_ = 0;
};

// class TRefableBase : public TRefable<TRefableBase> {
// public:
//     virtual ~TRefableBase() = default;
// };

class TMyObj final : public TRefable<TMyObj> {
// or if virtual dtor is required
// class TMyObj : public TRefableBase {
public:
    TMyObj(int i)
        : Data_(i)
    {}

    int GetData() const {
        return Data_;
    }

    ~TMyObj() {
        std::cout << "dtor" << std::endl;
    }

private:
    int Data_;
};

int main(int argc, char** argv) {
    TMyObj* obj = new TMyObj(2);

    TIntrusivePtrRefUnref<TMyObj> ptr1 = obj;
    TIntrusivePtrRefUnref<TMyObj> ptr2 = ptr1;
    TIntrusivePtrRefUnref<TMyObj> ptr3 = obj;
    return 0;
}
