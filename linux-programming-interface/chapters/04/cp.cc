#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>

// Functionality
// `tee <file>`
// 1. reads its stdin until EOF
// 2. writes it to <file>
// 3. writes it to stdout
// 4. if `-a` is suplied, do the append to <file>, instead of truncation

int main(int argc, char** argv) {
    int opt;
    int open_flags = O_TRUNC | O_WRONLY | O_CREAT;
    const char* out_file = NULL;
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                open_flags = O_APPEND | O_WRONLY | O_CREAT;
                break;
            default: /* '?' */
                exit(EXIT_FAILURE);
        }
    }

    if (optind > argc) exit(EXIT_FAILURE);

    out_file = argv[optind];
    return 0;
}

