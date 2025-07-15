#include "common.hh"

#include <cassert>
#include <signal.h>
#include <sys/mman.h>
#include <vector>

volatile sig_atomic_t sigsegv_occurred = 0;
volatile sig_atomic_t sigbus_occurred = 0;

static void sigsegv_handler(int sig)
{
    sigsegv_occurred = 1;
    return;
}

static void sigbus_handler(int sig)
{
    sigbus_occurred = 1;
    return;
}

int main(int argc, char** argv) {
    const auto PAGE_SIZE = sysconf(_SC_PAGESIZE);

    std::vector<char> file_contents;
    file_contents.assign(PAGE_SIZE * 10, 'o');
    file_contents.back() = 0;
    file_guard fg{"test.txt", file_contents.data()};
    int fd = open(fg.name, O_RDWR);
    char* addr = (char*)(mmap(NULL, PAGE_SIZE + 5, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0));
    close(fd);
    // printf("pid is %d\n", getpid());
    // sleep(1000);
    if (signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
        printf("couldn't install sigsegv error (errno=%s)", strerror(errno));
        exit(1);
    }
    if (signal(SIGBUS, sigbus_handler) == SIG_ERR) {
        printf("couldn't install sigbus error (errno=%s)", strerror(errno));
        exit(1);
    }

    // 1. referencing remainder of page
    addr[0] = 'b';                  // ok: on inside the
    addr[PAGE_SIZE + 228] = 'c';    // ok: outside mapping but still inside page boundaries
    addr[PAGE_SIZE * 10 + 1] = 'd';  // SIGSEGV: reference outside mapping
    pause();

    assert(sigsegv_occurred == 1);
    assert(sigbus_occurred == 0);
    sigsegv_occurred = 0;
    munmap(addr, PAGE_SIZE + 5);
    assert(errno == 0);

    // 2. referencing
}
