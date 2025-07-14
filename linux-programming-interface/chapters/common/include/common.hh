#pragma once
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string>

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
off_t get_offset(int fd);

bool is_fd_open(int fd);

std::string get_rss_status(void* addr, off_t length);
