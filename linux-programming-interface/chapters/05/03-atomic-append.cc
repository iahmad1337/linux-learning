#include "common.hh"

#include <cstdlib>
#include <unistd.h>

int main(int argc, char** argv) {
    const char* filename = argv[1];
    int num_bytes = atoi(argv[2]);
    int APPEND = O_APPEND;
    const char* symbol = "a";
    if (argc == 4) {
        switch(argv[3][0]) {
            case 'x': symbol = "a"; break;
            case 'y': symbol = "b"; break;
            default: APPEND = 0;
        }
    }
    auto fd = open(filename, O_CREAT | O_WRONLY | APPEND, REGULAR_FILE_PERMS);
    do {
        write(fd, symbol, 1);
        num_bytes--;
    } while (num_bytes > 0);
    close(fd);
}

