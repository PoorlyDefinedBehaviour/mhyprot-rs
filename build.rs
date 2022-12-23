fn main() {
    // Every cpp file must be included by calling file().
    cxx_build::bridge("src/lib.rs")
    .file("cpp/include/mhyprot.cpp")
    .file("cpp/include/file_utils.cpp")
    .file("cpp/include/service_utils.cpp")
    .file("cpp/include/win_utils.cpp")
    // Change flags to -std=c++20 if you are not using the visual studio compiler
    .flag("/std:c++20")
    .compile("mhyprot-rs");

    // Every header and cpp file must be included here.
    println!("cargo:rerun-if-changed=src/lib.rs");
    println!("cargo:rerun-if-changed=cpp/include/rust_bindings.hpp");
    println!("cargo:rerun-if-changed=cpp/include/mhyprot.hpp");
    println!("cargo:rerun-if-changed=cpp/include/mhyprot.cpp");
    println!("cargo:rerun-if-changed=cpp/include/file_utils.hpp");
    println!("cargo:rerun-if-changed=cpp/include/file_utils.cpp");
    println!("cargo:rerun-if-changed=cpp/include/logger.hpp");
    println!("cargo:rerun-if-changed=cpp/include/nt.hpp");
    println!("cargo:rerun-if-changed=cpp/include/raw_driver.cpp");
    println!("cargo:rerun-if-changed=cpp/include/service_utils.hpp");
    println!("cargo:rerun-if-changed=cpp/include/service_utils.cpp");
    println!("cargo:rerun-if-changed=cpp/include/sup.hpp");
    println!("cargo:rerun-if-changed=cpp/include/win_utils.hpp");
    println!("cargo:rerun-if-changed=cpp/include/win_utils.cpp");
}