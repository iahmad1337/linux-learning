#pragma once
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define REGULAR_FILE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

struct file_guard {
    file_guard(const char* name, const char* contents) : name{name} {
        auto fd = open(name, O_TRUNC | O_WRONLY | O_CREAT, REGULAR_FILE_PERMS);
        auto size = strlen(contents);
        write(fd, contents, size);
        close(fd);
    }

    ~file_guard() {
        unlink(name);
    }

    const char* name;
};

/// alternative to `tell` function
inline off_t get_offset(int fd) {
    return lseek(fd, 0, SEEK_CUR);
}

inline bool is_fd_open(int fd) {
    return fcntl(fd, F_GETFL) != EBADF;
}
