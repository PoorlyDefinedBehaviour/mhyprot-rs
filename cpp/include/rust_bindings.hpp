//! // Types and functions used by the Rust binding. The name of the c++ type alias must match the Rust type.

#include "cvrl.hpp"

using c_void = void;
using c_uint64_t = uint64_t;
using c_size_t = size_t;
using c_uint32_t = uint32_t;

bool cvrl_init() {
    return cvrl::init();
}

void cvrl_unload() {
	cvrl::unload();
}

bool driver_init(bool debug_prints = false, bool print_seeds = false) {
	return cvrl::driver_impl::driver_init(debug_prints, print_seeds);
}

bool read_kernel_memory(uint64_t* address, void* buffer, size_t* size) {
	return cvrl::driver_impl::read_kernel_memory(*address, buffer, *size);
}

bool read_user_memory(uint32_t* process_id, uint64_t* address, void* buffer, size_t* size) {
    return cvrl::driver_impl::read_user_memory(*process_id, *address, buffer, *size);
}

bool write_user_memory(uint32_t* process_id, uint64_t* address, void* buffer, size_t* size) {
    return cvrl::driver_impl::write_user_memory(*process_id, *address, buffer, *size);
}
