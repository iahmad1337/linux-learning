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
    void* addr;

    /****************
    *  mmap tests  *
    ****************/

    // 1. length != zero
    addr = mmap(NULL, 0, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1,  0);
    assert(errno == EINVAL);
    assert(addr == MAP_FAILED);
    errno = 0;

    // 2. addr exceeds virtual address space
    // addr = (void*)0x0fffffffffffffff;
    // addr = mmap(addr, 2 * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1,  0);
    // assert(errno == ENOMEM);
    // assert(addr == MAP_FAILED);
    // errno = 0;

    // 3. offset must be zero for anonymous mapping
    addr = mmap(NULL, 2 * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1,  1);
    assert(errno == EINVAL);
    assert(addr == MAP_FAILED);
    errno = 0;

    addr = mmap(NULL, 1024 * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1,  0);
    assert(errno == 0);
    assert(addr != MAP_FAILED);
    assert((uintptr_t)addr % PAGE_SIZE == 0);

    /*******************
    *  madvise tests  *
    *******************/

    const char contents[] = "Hello world!";
    memcpy(addr, contents, sizeof(contents));
    assert(strcmp((char*)addr, contents) == 0);

    // 0. task 50.2: check that MADV_DONTNEED replaces all values with 0s. Note,
    // that this will only happen with MAP_PRIVATE; in case of MAP_SHARED, the
    // pages may be simply swapped out
    madvise(addr, sizeof(contents), MADV_DONTNEED);
    assert(strcmp((char*)addr, contents) != 0);
    assert(((char*)addr)[0] == 0);

    // 1. non page-aligned addr
    madvise((void*)((uintptr_t)addr + 1), PAGE_SIZE, MADV_NORMAL);
    assert(errno == EINVAL);
    errno = 0;

    // 2. MADV_DONTNEED on mlocked pages
    mlock(addr, PAGE_SIZE);
    madvise(addr, PAGE_SIZE, MADV_DONTNEED);
    assert(errno == EINVAL);
    errno = 0;
    munlock(addr, PAGE_SIZE);

    // 3. invalid advice
    madvise(addr, PAGE_SIZE, 1337);
    assert(errno == EINVAL);
    errno = 0;

    munmap(addr, 1024 * PAGE_SIZE);
    assert(errno == 0);

    // 4. The mapping is too large
    addr = mmap(NULL, 32ull * 1024 * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    assert(errno == ENOMEM);
    errno = 0;
}
