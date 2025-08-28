#include "common.hh"
#include "sig-common.hh"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>

static volatile sig_atomic_t signalConcurrency = 0;
static volatile sig_atomic_t handlerCalls = 0;

void nodefer_handler(int sig) {
    signalConcurrency++;
    handlerCalls++;
    printf("The current call is %d\n", handlerCalls);
        fflush(stdout);
    if (signalConcurrency == 1) {
        printf("Sleeping for 20 seconds inside handler, please send another one\n");
        fflush(stdout);
        sleep(20);
    } else {
        assert(signalConcurrency == 2);
        printf("Successfully observed second entry to signal handler\n");
    }
    signalConcurrency--;
}

int
main(int argc, char *argv[])
{
    int n, numSecs;
    sigset_t pendingMask, blockingMask, emptyMask;

    printf("%s: PID is %ld\n", argv[0], (long) getpid());

    struct sigaction sa;
    sa.sa_handler = nodefer_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_NODEFER;

    for (n = 1; n < NSIG; n++)          /* Same handler for all signals */
        sigaction(n, &sa, NULL);         /* Ignore errors */

    if (argc > 1) {
        numSecs = atoi(argv[1]);
        assert(numSecs > 0);
    } else {
        numSecs = 5;
    }

    sleep(numSecs);

    printf("Finished without interruptions\n");

    exit(EXIT_SUCCESS);
}
