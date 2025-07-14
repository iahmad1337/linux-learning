#include "common.hh"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/mman.h>

const auto PAGE_SIZE = sysconf(_SC_PAGESIZE);

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("usage: %s <src> <dst>\n", argv[0]);
        exit(1);
    }
    const char* src = argv[1];
    const char* dst = argv[2];

    int fd = open(src, O_RDONLY);
    if (fd == -1) {
        printf("error opening file %s (errno=%s)\n", src, strerror(errno));
        exit(1);
    }

    struct stat fs;
    fstat(fd, &fs);
    char* src_addr = (char*)mmap(NULL, fs.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (src_addr == MAP_FAILED) {
        printf("error mmaping file %s (errno=%s)\n", src, strerror(errno));
        exit(1);
    }

    int out_fd = open(dst, O_RDWR | O_CREAT, 0666);
    if (out_fd == -1) {
        printf("error opening file %s (errno=%s)\n", dst, strerror(errno));
        exit(1);
    }
    if (ftruncate(out_fd, fs.st_size) == -1) {
        printf("couldn't resize dst file (errno=%s)\n", strerror(errno));
        exit(1);
    }
    // MAP_PRIVATE does not carry the changes to file, so we MUST use
    // MAP_SHARED!
    char* dst_addr = (char*)mmap(NULL, fs.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, out_fd, 0);
    if (dst_addr == MAP_FAILED) {
        printf("error mmaping destination file %s (errno=%s)\n", dst, strerror(errno));
        exit(1);
    }

    memcpy(dst_addr, src_addr, fs.st_size);
    assert(memcmp(dst_addr, src_addr, fs.st_size) == 0);

    munmap(dst_addr, fs.st_size);
    close(out_fd);

    munmap(src_addr, fs.st_size);
    close(fd);
}
