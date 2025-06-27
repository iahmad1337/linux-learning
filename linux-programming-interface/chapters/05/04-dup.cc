#include "common.hh"

#include <cassert>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

namespace mine {
    int dup(int oldfd) {
        return fcntl(oldfd, F_DUPFD, 0);
    }

    namespace detail {
        int dupImpl(int oldfd, int newfd, bool cloexec) {
        if (oldfd == newfd) {
            if (is_fd_open(oldfd)) {
                return newfd;
            } else {
                return -1;
            }
        }

        int flag = cloexec ? F_DUPFD_CLOEXEC : F_DUPFD;

        int realfd = fcntl(oldfd, flag, newfd);
        if (realfd != newfd) {
            close(newfd);
            close(realfd);
            realfd = fcntl(oldfd, flag, newfd);
        }

        assert(realfd == newfd);
        return realfd;
        }
    }

    int dup2(int oldfd, int newfd) {
        return detail::dupImpl(oldfd, newfd, false);
    }

    int dup3(int oldfd, int newfd, int flags) {
        return detail::dupImpl(oldfd, newfd, flags & O_CLOEXEC);
    }
}  // namespace mine

int main(int argc, char** argv) {
    file_guard fg{"dummy_file", "abcdefghijklmnopqrstuvwxyz"};

    {
        // dup test
        int fd = open("dummy_file", O_RDONLY);
        char buf[1024];
        read(fd, buf, 3);
        assert(get_offset(fd) == 3);
        int fd2 = mine::dup(fd);
        assert(get_offset(fd2) == 3);

        read(fd, buf, 2);
        assert(get_offset(fd) == 5);
        assert(get_offset(fd2) == 5);

        close(fd);
        read(fd2, buf, 4);
        assert(get_offset(fd2) == 9);

        int fd3 = mine::dup(fd2);
        assert(fd3 == fd);
        assert(get_offset(fd3) == 9);

        close(fd2);
        close(fd3);
    }

    {
        // dup2 test
        int fd = open("dummy_file", O_RDONLY);
        char buf[1024];
        int fd2 = mine::dup2(fd, 4);
        assert(fd2 == 4);
        close(fd2);

        fd2 = mine::dup2(fd, 5);
        assert(fd2 == 5);

        read(fd2, buf, 1);
        read(fd, buf, 2);
        assert(get_offset(fd) == 3);

        int fd3 = mine::dup2(fd, fd2);
        assert(fd3 == fd2);

        read(fd3, buf, 4);
        assert(get_offset(fd) == 7);
        close(fd);
        close(fd3);
    }
    {
        // dup3 test
        int fd = open("dummy_file", O_RDONLY);
        assert(fd == 3);

        // this file descriptor will be closed on execve
        int fd2 = mine::dup3(fd, fd+1, O_CLOEXEC);
        assert(fd2 == 4);

        const char* args[] = {
            "/bin/bash",
            "-c",
            // check, that there is only one file descriptor for dummy_file
            "ls -lA /proc/self/fd | grep dummy_file | wc -l | xargs test 1 -eq"
            " && echo SUCCESS || echo FAIL",
            nullptr,
        };
        const char* envp[] = {
            nullptr
        };
        execve(args[0], (char* const*)args, (char* const*)envp);
    }
}

