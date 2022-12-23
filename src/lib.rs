// type c_void = std::ffi::c_void;
// type c_uint64_t = std::ffi::c_long;
// type c_size_t = std::ffi::c_ulong;

/// Pointers are mut even when they are not meant to be mutated
/// so the generated c code uses a *T instead of a const *T.
#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("cvrl-rs/cpp/include/rust_bindings.hpp");

        type c_void;
        type c_uint64_t;
        type c_uint32_t;
        type c_size_t;

        fn cvrl_init() -> bool;
        fn cvrl_unload();

        fn driver_init(debug_prints: bool, print_seeds: bool) -> bool;

        unsafe fn read_kernel_memory(
            address: *mut c_uint64_t,
            buffer: *mut c_void,
            size: *mut c_size_t,
        ) -> bool;

        unsafe fn read_user_memory(
            process_id: *mut c_uint32_t,
            address: *mut c_uint64_t,
            buffer: *mut c_void,
            size: *mut c_size_t,
        ) -> bool;

        unsafe fn write_user_memory(
            process_id: *mut c_uint32_t,
            address: *mut c_uint64_t,
            buffer: *mut c_void,
            size: *mut c_size_t,
        ) -> bool;
    }
}

pub use ffi::*;
