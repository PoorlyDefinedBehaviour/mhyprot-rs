// use cxx::UniquePtr;

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("myphrot-rs/cpp/include/myphrot.h");

        type BlobstoreClient;

        fn new_blobstore_client() -> UniquePtr<BlobstoreClient>;
    }
}

fn main() {
    let client = ffi::new_blobstore_client();
}
