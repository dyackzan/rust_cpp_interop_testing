#pragma once

// Forward‐declare the Rust type and functions as C symbols
extern "C" {
    /// Opaque handle; definition only lives in Rust.
    struct MyRustObj;

    // allocator / deallocator
    MyRustObj* my_rust_obj_new(int initial);
    void         my_rust_obj_free(MyRustObj* ptr);

    // method
    void         my_rust_obj_do_something(MyRustObj* ptr);
}

/// C++ wrapper that “owns” the Rust object and frees it in its destructor.
class MyObj {
public:
    explicit MyObj(const int initial)
      : bridge_(my_rust_obj_new(initial))
    {}

    ~MyObj() {
        my_rust_obj_free(bridge_);
    }

    // non‐copyable (the rust pointer would be double‐freed)
    MyObj(const MyObj&) = delete;
    MyObj& operator=(const MyObj&) = delete;

    // movable
    MyObj(MyObj&& o) noexcept
      : bridge_(o.bridge_)
    { o.bridge_ = nullptr; }

    MyObj& operator=(MyObj&& o) noexcept {
        if(this != &o) {
            my_rust_obj_free(bridge_);
            bridge_ = o.bridge_;
            o.bridge_ = nullptr;
        }
        return *this;
    }

    void doSomething() {
        my_rust_obj_do_something(bridge_);
    }

private:
    MyRustObj* bridge_;  ///< opaque pointer into Rust heap
};
