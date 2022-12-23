// use cxx::UniquePtr;

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("myphrot-rs/cpp/include/myphrot.h");

        // type BlobstoreClient;

        fn test_123();
    }
}

fn main() {
    let client = ffi::test_123();
}
