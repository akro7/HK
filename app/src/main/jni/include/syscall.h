#include <sys/syscall.h>

#ifdef __aarch64__
__attribute__((always_inline)) inline long __syscall_arm64(long sysno, long arg1 = 0, long arg2 = 0, long arg3 = 0, long arg4 = 0, long arg5 = 0, long arg6 = 0) {
    long ret;
    register long x0 asm("x0") = arg1;
    register long x1 asm("x1") = arg2;
    register long x2 asm("x2") = arg3;
    register long x3 asm("x3") = arg4;
    register long x4 asm("x4") = arg5;
    register long x5 asm("x5") = arg6;
    register long x8 asm("x8") = sysno;
    
    asm volatile(
        "svc #0\n"
        : "=r" (x0)
        : "r" (x0), "r" (x1), "r" (x2), "r" (x3), "r" (x4), "r" (x5), "r" (x8)
        : "memory", "cc"
    );
    
    return x0;
}

#define SYSCALL(sysno, ...) __syscall_arm64(sysno, ##__VA_ARGS__)
#endif

#ifdef __arm__
__attribute__((always_inline)) inline long __syscall_arm32(long sysno, long arg1 = 0, long arg2 = 0, long arg3 = 0, long arg4 = 0, long arg5 = 0, long arg6 = 0) {
    register long r0 asm("r0") = arg1;
    register long r1 asm("r1") = arg2;
    register long r2 asm("r2") = arg3;
    register long r3 asm("r3") = arg4;
    register long r4 asm("r4") = arg5;
    register long r5 asm("r5") = arg6;
    register long r7 asm("r7") = sysno;

    asm volatile(
        "svc #0\n"
        : "=r" (r0)
        : "r" (r0), "r" (r1), "r" (r2), "r" (r3), "r" (r4), "r" (r5), "r" (r7)
        : "memory", "cc"
    );

    return r0;
}

#define SYSCALL(sysno, ...) __syscall_arm32(sysno, ##__VA_ARGS__)
#endif
