fn main() {
    // Every cpp file must be included by calling file().
    cxx_build::bridge("src/main.rs")
    .file("cpp/include/myphrot.cpp")
    .flag_if_supported("-std=c++17")
    .compile("myphrot-rs");

    // Every header and cpp file must be included here.
    println!("cargo:rerun-if-changed=src/main.rs");
    println!("cargo:rerun-if-changed=cpp/include/myphrot.cpp");
    println!("cargo:rerun-if-changed=cpp/include/myphrot.h");
}