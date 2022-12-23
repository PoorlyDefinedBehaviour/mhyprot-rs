## Based on

https://codentium.com/guides/windows-dev/windows-drivers-in-rust-hello-world/

## Dependencies

- Microsoft Visual Studio
- Windows SDK
- Windows Driver Kit
- LLVM and Clang (for bindgen)
- Microsoft Windows running in Testing Mode (to load self-signed Windows drivers)
- Sysinternals DebugView

## Install the correct rust toolchain

```
rustup toolchain install nightly-x86_64-pc-windows-msvc
```

### If rust-analyzer does not work, use the nightly toolchain

```
rustup install nightly
rustup default nightly
```