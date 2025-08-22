/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2024.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 20-6 */

/* sig_sender.c

   Usage: sig_sender PID num-sigs sig [sig2]

   Send signals to sig_receiver.c.

   Sends 'num-sigs' signals of type 'sig' to the process with the specified PID.
   If a fourth command-line argument is supplied, send one instance of that
   signal, after sending the previous signals.
*/
#include <cassert>
#include <signal.h>
#include "common.hh"

int
main(int argc, char *argv[])
{
    int numSigs, sig, j;
    pid_t pid;

    if (argc < 4 || strcmp(argv[1], "--help") == 0)
        report_error("usage:\n    %s pid num-sigs sig-num [sig-num-2]\n", argv[0]);

    pid = atol(argv[1]);
    numSigs = atoi(argv[2]);
    assert(numSigs > 0);
    sig = atoi(argv[3]);

    /* Send signals to receiver */

    printf("%s: sending signal %d to process %ld %d times\n",
            argv[0], sig, (long) pid, numSigs);

    for (j = 0; j < numSigs; j++)
        if (kill(pid, sig) == -1)
            report_error("kill failed: pid=%zu sig=%d", pid, sig);

    /* If a fourth command-line argument was specified, send that signal */

    if (argc > 4) {
        int sig2 = atoi(argv[4]);
        if (kill(pid, sig2) == -1)
            report_error("kill failed for second signal: pid=%zu sig=%d", pid, sig);
    }

    printf("%s: exiting\n", argv[0]);
    exit(EXIT_SUCCESS);
}
