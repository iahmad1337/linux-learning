#include "common.hh"
#include "sig-common.hh"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>

int
main(int argc, char *argv[])
{
    int n, numSecs;
    sigset_t pendingMask, blockingMask, emptyMask;

    printf("%s: PID is %ld\n", argv[0], (long) getpid());

    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);

    if (argc > 1) {
        numSecs = atoi(argv[1]);
        assert(numSecs > 0);
    } else {
        numSecs = 5;
    }

    if (argc > 2) {
        if (argv[2][0] == 'D') {
            sa.sa_handler = SIG_DFL;
        }
    }

    for (n = 1; n < NSIG; n++)          /* Same handler for all signals */
        sigaction(n, &sa, NULL);         /* Ignore errors */

    sigfillset(&blockingMask);
    if (sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1) report_error("sigprocmask(blocking)");
    sleep(numSecs);
    if (sigpending(&pendingMask) != -1) {
        printSigset(stdout, "    ", &pendingMask);
    }

    printf("Unblocking signals and waiting for their handling...\n");
    sigemptyset(&emptyMask);
    if (sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1) report_error("sigprocmask(blocking)");

    printf("Finished without interruptions\n");

    exit(EXIT_SUCCESS);
}
