// #[repr(c)] tells Rust to lay out the struct in memory using the same rules as the C programming
// language. This ensures compatibility with C FFI calls.
#[repr(C)]
pub struct MyRustObj {
    value: i32,
}

impl MyRustObj {
    fn do_something(&mut self) {
        self.value += 1;
        println!("👉 MyRustObj.value is now {}", self.value);
    }
}

/// Allocate a new `MyRustObj` on the Rust heap and return a raw pointer.
#[no_mangle]
pub extern "C" fn my_rust_obj_new(initial: i32) -> *mut MyRustObj {
    let boxed = Box::new(MyRustObj { value: initial });
    Box::into_raw(boxed)
}

/// Call a method on the object.  Safety: `ptr` must come from `my_rust_obj_new`.
#[no_mangle]
pub extern "C" fn my_rust_obj_do_something(ptr: *mut MyRustObj) {
    if ptr.is_null() {
        return;
    }
    // SAFETY: we trust the caller
    let obj: &mut MyRustObj = unsafe { &mut *ptr };
    obj.do_something();
}

/// Free the object, pairing exactly the allocation above.
#[no_mangle]
pub extern "C" fn my_rust_obj_free(ptr: *mut MyRustObj) {
    if ptr.is_null() {
        return;
    }
    // SAFETY: reclaim the Box and drop it
    unsafe { let _ = Box::from_raw(ptr); }
}
