#include <iostream>
#include <optional>

#include <lib/raii.h>
#include <lib/intrusive_ptr.h>
#include <lib/intrusive_ptr_via_methods.h>

class SomeObj {
public:
    ~SomeObj() {
        std::cout << "dtor\n";
    }
private:
    size_t Counter_ = 0;

    friend void intrusive_ptr_add_ref(SomeObj* p);
    friend void intrusive_ptr_release(SomeObj* p);
};


void intrusive_ptr_add_ref(SomeObj* p) {
    ++p->Counter_;
}

void intrusive_ptr_release(SomeObj* p) {
    --p->Counter_;
    if (p->Counter_ == 0) {
        delete p;
    }
}

class SomeObjWithMethods : public TRef<SomeObjWithMethods> {
public:
    ~SomeObjWithMethods() {
        std::cout << "dtor\n";
    }
};

int main(int argc, char** argv) {
    // std::cout << "before\n";
    // DEFER {
    //     std::cout << "RAII\n";
    // };
    // DEFER {
    //     std::cout << "RAII\n";
    // };
    // std::cout << "after\n";
    // std::optional<int> op;
    // auto* objPtr = new SomeObj();
    // TIntrusivePtr<SomeObj> ptr1(objPtr);
    // TIntrusivePtr<SomeObj> ptr2(objPtr);

    auto* objPtr = new SomeObjWithMethods();
    TIntrusivePtrViaMethods<SomeObjWithMethods> ptr1(objPtr);
    TIntrusivePtrViaMethods<SomeObjWithMethods> ptr2(objPtr);

}
