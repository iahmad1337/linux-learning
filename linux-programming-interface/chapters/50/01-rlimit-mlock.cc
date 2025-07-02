#include "common.hh"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/mman.h>

const auto PAGE_SIZE = sysconf(_SC_PAGESIZE);

int main(int argc, char** argv) {
    rlimit rlim;
    getrlimit(RLIMIT_MEMLOCK, &rlim);
    printf("RLIMIT_MEMLOCK: cur=%lu max=%lu\n", rlim.rlim_cur, rlim.rlim_max);

    // 1. Set the soft limit to low value
    rlim.rlim_cur = PAGE_SIZE;
    setrlimit(RLIMIT_MEMLOCK, &rlim);
    getrlimit(RLIMIT_MEMLOCK, &rlim);
    assert(rlim.rlim_cur == PAGE_SIZE);

    char buf[PAGE_SIZE * 10];
    void* aligned_addr = (void*)(((uintptr_t)buf) & ~(PAGE_SIZE - 1));

    // 2. Try to lock no more than one page - should succeed
    mlock(aligned_addr, PAGE_SIZE);
    assert(errno == 0);

    // 3. Try to lock more memory - should fail
    mlock(aligned_addr, PAGE_SIZE * 2);
    assert(errno == ENOMEM);
}
