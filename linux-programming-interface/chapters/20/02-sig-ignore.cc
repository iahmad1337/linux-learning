/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2024.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 20-7 */

/* sig_receiver.c

   Usage: sig_receiver [block-time]

   Catch and report statistics on signals sent by sig_sender.c.

   Note that although we use signal() to establish the signal handler in this
   program, the use of sigaction() is always preferable for this task.
*/
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

    /* Here we use the simpler signal() API to establish a signal handler,
       but for the reasons described in Section 22.7 of TLPI, sigaction()
       is the (strongly) preferred API for this task. */

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    for (n = 1; n < NSIG; n++)          /* Same handler for all signals */
        sigaction(n, &sa, NULL);         /* Ignore errors */

    /* If a sleep time was specified, temporarily block all signals,
       sleep (while another process sends us signals), and then
       display the mask of pending signals and unblock all signals */

    if (argc > 1) {
        numSecs = atoi(argv[1]);
        assert(numSecs > 0);

        sigfillset(&blockingMask);
        if (sigprocmask(SIG_SETMASK, &blockingMask, NULL) == -1)
            report_error("sigprocmask");

        printf("%s: sleeping for %d seconds\n", argv[0], numSecs);
        sleep(numSecs);

        if (sigpending(&pendingMask) == -1)
            report_error("sigpending");

        printf("%s: pending signals are: \n", argv[0]);
        printSigset(stdout, "\t\t", &pendingMask);

        sigemptyset(&emptyMask);        /* Unblock all signals */
        if (sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
            report_error("sigprocmask");
    }

    while (!gotSigint)                  /* Loop until SIGINT caught */
        continue;

    for (n = 1; n < NSIG; n++)          /* Display number of signals received */
        if (sigCnt[n] != 0)
            printf("%s: signal %d caught %d time%s\n", argv[0], n,
                    sigCnt[n], (sigCnt[n] == 1) ? "" : "s");

    exit(EXIT_SUCCESS);
}
