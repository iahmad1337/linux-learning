#include "common.hh"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    file_guard fg{"dummy_file", "abcdefghijklmnopqrstuvwxyz"};
    int fd = open("dummy_file", O_RDWR | O_CREAT | O_CLOEXEC);
    char buf[1024];
    read(fd, buf, 3);
    int fd2 = dup(fd);

    assert(get_offset(fd) == get_offset(fd2));
    assert(fcntl(fd, F_GETFL) == fcntl(fd2, F_GETFL));  // they share O_RDWR status flag
}

