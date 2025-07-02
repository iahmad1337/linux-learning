#include "common.hh"

#include <cstdlib>
#include <unistd.h>

int main(int argc, char** argv) {
    file_guard fg{"dummy_file", "abcdefghijklmnopqrstuvwxyz"};
    auto fd = open("dummy_file", O_WRONLY | O_APPEND);
    lseek(fd, 0, SEEK_SET);
    write(fd, "1337", 4);
    close(fd);
    // So here we see, that "1337" is actually appended to the end
    system("cat dummy_file");
}
