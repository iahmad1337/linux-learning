#include "common.hh"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    char buf[1024];

    int fd1 = open("file", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    int fd2 = dup(fd1);
    int fd3 = open("file", O_RDWR);
    write(fd1, "Hello,", 6);
    write(fd2, "world", 6);
    lseek(fd2, 0, SEEK_SET);
    write(fd1, "HELLO,", 6);
    write(fd3, "Gidday", 6);

    // copy and paste this piece of code between the lines
    lseek(fd1, 0, SEEK_SET);
    memset(buf, 0, sizeof(buf));
    read(fd1, buf, 100);
    puts(buf);
}

