#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>

// Functionality
// `cp <source> <destination>`
// 1. copy source to destination
// 2. save the holes

int main(int argc, char** argv) {
    int opt;
    int open_flags = O_TRUNC | O_WRONLY | O_CREAT;
    const char* in_file = NULL;
    const char* out_file = NULL;

    if (argc < 3) exit(EXIT_FAILURE);

    in_file = argv[1];
    out_file = argv[2];

    int in_fd = open(in_file, O_RDONLY);
    int out_fd = open(out_file, O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    constexpr size_t BUF_SIZE = 4 * 1024;
    char buf[BUF_SIZE];
    off_t offset = 0;
    while (true) {
        offset = lseek(in_fd, offset, SEEK_DATA);
        if (offset == -1) {
            // we point past-the-end => explicitly write the hole and exit
            lseek(out_fd, lseek(in_fd, 0, SEEK_CUR), SEEK_SET);
            break;
        }
        int bytes_read = read(in_fd, buf, BUF_SIZE);

        if (bytes_read <= 0) {
            break;
        }
        lseek(out_fd, offset, SEEK_SET);
        write(out_fd, buf, bytes_read);
        offset = offset + bytes_read;
    }
    close(out_fd);
    close(in_fd);
    // while ((bytes_read = read(in_fd, buf, BUF_SIZE)) > 0) {
    //     // TODO: use lseek + SEEK_HOLE/SEEK_DATA, since reading through holes
    //     // manually may be very time consuming (prove this with a very large
    //     // file + maybe `strace --syscall-times`)
    // }
    return 0;
}

