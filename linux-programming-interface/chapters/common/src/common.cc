#include "common.hh"
#include <sys/mman.h>

off_t get_offset(int fd) {
    return lseek(fd, 0, SEEK_CUR);
}

bool is_fd_open(int fd) {
    return fcntl(fd, F_GETFL) != EBADF;
}


std::string get_rss_status(void* addr, off_t length) {
    const off_t PAGE_SIZE = sysconf(_SC_PAGESIZE);
    const size_t WIDTH = 16;
    addr = (void*)((uintptr_t)addr & ~(PAGE_SIZE - 1));
    length = (length + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
    std::basic_string<unsigned char> vec;
    vec.resize(length / PAGE_SIZE);
    mincore(addr, length, &vec[0]);

    std::string result;
    for (size_t i = 0; i < vec.size(); i++) {
        result.push_back('0' + (vec[i] & 1));
        if ((i + 1) % WIDTH == 0) {
            result.push_back('\n');
        }
    }
    return result;
}
