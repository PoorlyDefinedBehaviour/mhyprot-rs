use std::path::Path;

fn main() {
    cxx_build::bridge("src/main.rs")
    .file("cpp/include/myphrot.cpp")
    .flag_if_supported("-std=c++17")
    .compile("myphrot-rs");
}