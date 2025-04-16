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


// TODO: test
// ""
// "    "
// "\n\n"
// "     hello"
// "hello    "
// " hello "
// "  hello my name is  "
// "  hey you "
void trim_inplace(char* buf) {
    size_t start = 0;
    while (buf[start] != 0 && isspace(buf[start])) {
        start++;
    }
    size_t i = start;
    size_t end = 0;
    while (buf[i] != 0) {
        if (!isspace(buf[i])) end = i;
        i++;
    }

    for (i = 0; i < end - start; i++) {
        buf[i] = buf[start + i];
    }
    buf[end - start] = 0;
}

void dedent_inplace(char* buf) {
    size_t least_indent = std::numeric_limits<size_t>::max();
    // indent - number of spaces between "\n" and the next non-space char
    for (size_t i = 0; buf[i] != 0;) {
        size_t j = 0;
        while (buf[i + j] != '\n') {
            j++;
        }
        while (buf[i + j] == '\n') {
            j++;
        }
        // now, buf[i+j] is the first char after '\n'
        size_t indent = 0;
        while (buf[i + j] == ' ') {
            indent++;
            j++;
        }
        if (!isspace(buf[i + j])) least_indent = std::min(least_indent, indent);
        // TODO: very hard(((
    }
}

void test() {
}

void expect(const char* message, bool condition) {
    if (!condition) {
        puts(message);
        exit(EXIT_FAILURE);
    }
}

void usage(int argc, char** argv) {
    char buf[1024];
    sprintf(buf,
R"(
Usage:
    %s -h <hole count> -o <output file>
)",
        argv[0]
    );
    // dedent_inplace(buf);
    // trim_inplace(buf);
    puts(buf);
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
    if (getenv("TEST")) test();

    int opt;
    int open_flags = O_TRUNC | O_WRONLY | O_CREAT;
    const char* out_file = nullptr;
    int holes = 1;
    while ((opt = getopt(argc, argv, "h:o:")) != -1) {
        switch (opt) {
            case 'o':
                out_file = optarg;
                break;
            case 'h':
                holes = atoi(optarg);
                break;
            default: /* '?' */
                usage(argc, argv);
        }
    }
    if (!out_file || holes == 0) usage(argc, argv);

    int out_fd = open(out_file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    expect("outfile can't be opened", out_fd != -1);

    // 64 MiB
    constexpr size_t HOLE_SIZE = 1024 * 1024 * 64;

    bool is_hole = false;
    while (holes != 0) {
        if (is_hole) {
            lseek(out_fd, HOLE_SIZE, SEEK_CUR);
            holes--;
        } else {
            write(out_fd, "a", 1);
        }
        is_hole = !is_hole;
    }
    close(out_fd);

    // Compact the actual file
    char buf[1024];
    sprintf(buf, "fallocate -d %s", out_file);
    system(buf);
    return 0;
}
