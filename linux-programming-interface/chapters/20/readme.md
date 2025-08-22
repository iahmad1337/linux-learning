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
