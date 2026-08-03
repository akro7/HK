/* Compatibility shims for legacy GCC __sync_* builtins missing on armeabi-v7a
 * with modern NDK toolchains (needed by prebuilt OpenSSL libcrypto.a).
 *
 * Clang recognizes __sync_* names as builtins and refuses a normal
 * redeclaration, so each function is defined under a different C name
 * and bound to the required symbol name via an asm label. */

#include <stdint.h>

int __sync_add_and_fetch_4_impl(volatile void *ptr, int value) asm("__sync_add_and_fetch_4");
int __sync_add_and_fetch_4_impl(volatile void *ptr, int value) {
    return __atomic_add_fetch((volatile int *)ptr, value, __ATOMIC_SEQ_CST);
}

int __sync_sub_and_fetch_4_impl(volatile void *ptr, int value) asm("__sync_sub_and_fetch_4");
int __sync_sub_and_fetch_4_impl(volatile void *ptr, int value) {
    return __atomic_sub_fetch((volatile int *)ptr, value, __ATOMIC_SEQ_CST);
}

int __sync_fetch_and_add_4_impl(volatile void *ptr, int value) asm("__sync_fetch_and_add_4");
int __sync_fetch_and_add_4_impl(volatile void *ptr, int value) {
    return __atomic_fetch_add((volatile int *)ptr, value, __ATOMIC_SEQ_CST);
}

int __sync_fetch_and_sub_4_impl(volatile void *ptr, int value) asm("__sync_fetch_and_sub_4");
int __sync_fetch_and_sub_4_impl(volatile void *ptr, int value) {
    return __atomic_fetch_sub((volatile int *)ptr, value, __ATOMIC_SEQ_CST);
}

int __sync_bool_compare_and_swap_4_impl(volatile void *ptr, int oldval, int newval) asm("__sync_bool_compare_and_swap_4");
int __sync_bool_compare_and_swap_4_impl(volatile void *ptr, int oldval, int newval) {
    return __atomic_compare_exchange_n((volatile int *)ptr, &oldval, newval, 0,
                                        __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

int __sync_val_compare_and_swap_4_impl(volatile void *ptr, int oldval, int newval) asm("__sync_val_compare_and_swap_4");
int __sync_val_compare_and_swap_4_impl(volatile void *ptr, int oldval, int newval) {
    __atomic_compare_exchange_n((volatile int *)ptr, &oldval, newval, 0,
                                 __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    return oldval;
}

int __sync_lock_test_and_set_4_impl(volatile void *ptr, int value) asm("__sync_lock_test_and_set_4");
int __sync_lock_test_and_set_4_impl(volatile void *ptr, int value) {
    return __atomic_exchange_n((volatile int *)ptr, value, __ATOMIC_SEQ_CST);
}

void __sync_lock_release_4_impl(volatile void *ptr) asm("__sync_lock_release_4");
void __sync_lock_release_4_impl(volatile void *ptr) {
    __atomic_store_n((volatile int *)ptr, 0, __ATOMIC_SEQ_CST);
}
