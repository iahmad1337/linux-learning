#include "common.hh"

off_t get_offset(int fd) {
    return lseek(fd, 0, SEEK_CUR);
}

bool is_fd_open(int fd) {
    return fcntl(fd, F_GETFL) != EBADF;
}
