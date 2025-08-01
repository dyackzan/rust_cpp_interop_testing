// main.cpp
#include "MyObj.hpp"

int main() {
    MyObj obj(42);
    obj.doSomething();
    obj.doSomething();

    // destructor automatically calls `my_rust_obj_free`
    return 0;
}
