The signal mask can be viewed via `/proc/<PID>/status` in the following fields:
```
SigPnd: 0000000000000000
ShdPnd: 0000000000000000
SigBlk: 0000000000000000
SigIgn: 0000000000300000
SigCgt: 00000000480854ee
```
Where
> SigPnd (per-thread pending signals), ShdPnd (process-wide pending
> signals; since Linux 2.6), SigBlk (blocked signals), SigIgn (ignored signals), and
> SigCgt (caught signals)
> -- tlpi 20.1
# Testing
## 01. send-receive
```
 7593  [2025-08-20 19:31:23] ./20/bin/01-sig-receiver 40 &
 7594  [2025-08-20 19:31:35] ./20/bin/01-sig-sender 26722 100 1 2
 7595  [2025-08-20 19:31:38] ./20/bin/01-sig-sender 26722 100 3 2
 7596  [2025-08-20 19:31:40] ./20/bin/01-sig-sender 26722 100 4 2
 7597  [2025-08-20 19:31:46] ./20/bin/01-sig-sender 26722 100 5 2
 7598  [2025-08-20 19:31:49] ./20/bin/01-sig-sender 26722 100 6 2
 7599  [2025-08-20 19:31:51] ./20/bin/01-sig-sender 26722 100 20 2
 7600  [2025-08-20 19:31:54] ./20/bin/01-sig-sender 26722 100 23 2
 7601  [2025-08-20 19:31:58] ./20/bin/01-sig-sender 26722 100 18 2
 7602  [2025-08-20 19:32:02] ./20/bin/01-sig-sender 26722 100 19 2
 7603  [2025-08-20 19:32:09] ps
 7604  [2025-08-20 19:32:46] ./20/bin/01-sig-sender 26722 100 18 2

And then:

$ ./20/bin/01-sig-sender 26722 100 18 2
./20/bin/01-sig-sender: sending signal 18 to process 26722 100 times
./20/bin/01-sig-receiver: pending signals are:
                1 (Hangup)
                2 (Interrupt)
                3 (Quit)
                4 (Illegal instruction)
                5 (Trace/breakpoint trap)
                6 (Aborted)
                18 (Continued)
                23 (Urgent I/O condition)
./20/bin/01-sig-receiver: signal 1 caught 1 time
./20/bin/01-sig-receiver: signal 3 caught 1 time
./20/bin/01-sig-receiver: signal 4 caught 1 time
./20/bin/01-sig-receiver: signal 5 caught 1 time
./20/bin/01-sig-receiver: signal 6 caught 1 time
./20/bin/01-sig-receiver: signal 18 caught 2 times
./20/bin/01-sig-receiver: signal 23 caught 1 time
./20/bin/01-sig-sender: exiting
[1]+  Done                    ./20/bin/01-sig-receiver 40
```
=======

## 02. SIG_IGNORE
With default signal handler (SIG_DFL) we see that pending signals are handled in
a standard manner when unblocked:
```
 1565  [2025-08-28 21:46:46] ./20/bin/02-sig-ignore 60 D &
 1566  [2025-08-28 21:46:54] ./20/bin/01-sig-sender 122934 100 15
 1567  [2025-08-28 21:47:01] ./20/bin/01-sig-sender 122934 8 11
 1568  [2025-08-28 21:47:05] ./20/bin/01-sig-sender 122934 1 2
 1569  [2025-08-28 21:47:14] ./20/bin/01-sig-sender 122934 13 14
```
the finish:
```
$     2 (Interrupt)
    11 (Segmentation fault)
    14 (Alarm clock)
    15 (Terminated)
Unblocking signals and waiting for their handling...

[1]+  Segmentation fault      ./20/bin/02-sig-ignore 60 D
```

With SIG_IGN, however, the pending signals, when unblocked, are just ignored and
program successfelly finishes as if nothing happened:
```
 1572  [2025-08-28 21:52:36] ./20/bin/02-sig-ignore 60 &
 1573  [2025-08-28 21:52:45] ./20/bin/01-sig-sender 123184 8 11
 1574  [2025-08-28 21:52:48] ./20/bin/01-sig-sender 123184 14 15
 1575  [2025-08-28 21:52:57] ./20/bin/01-sig-sender 123184 11 2
 1576  [2025-08-28 21:53:14] ./20/bin/01-sig-sender 123184 6 5
```
& the finish:
```
$     2 (Interrupt)
    5 (Trace/breakpoint trap)
    11 (Segmentation fault)
    15 (Terminated)
Unblocking signals and waiting for their handling...

[1]+  Trace/breakpoint trap   ./20/bin/02-sig-ignore 60
```
