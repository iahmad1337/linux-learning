// Make a file with lots of large holes, so that naive cp impleme

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>
#include <cctype>
#include <limits>

void error(const char* msg) {
    puts(msg);
    exit(1);
}

int main(int argc, char** argv) {

    int in_fd = open(argv[1], O_RDONLY);
    if (in_fd < 0) {
        error("wc: could not open file for reading");
    }

    // 64 MiB
    constexpr size_t BUF_SIZE = 1024 * 64;
    char buf[BUF_SIZE];

    size_t answer = 0;
    int bytes_read = 0;

    while ((bytes_read = read(in_fd, buf, sizeof(buf))) > 0) {
        if (bytes_read < 0) {
            error("wc: error occurred while reading file");
        }
        answer += bytes_read;
    }
    printf("%zu\n", answer);
    return 0;
}

