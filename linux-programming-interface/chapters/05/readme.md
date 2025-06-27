# 03. Testing
```
 1050  [2025-06-11 22:09:43] cmake --build build --target install && ./bin/03-atomic-append kek 100000
 1051  [2025-06-11 22:09:47] ll
 1052  [2025-06-11 22:09:53] cmake --build build --target install && ./bin/03-atomic-append kek 100000 x
 1053  [2025-06-11 22:09:55] ll
 1054  [2025-06-11 22:10:22] cmake --build build --target install && ./bin/03-atomic-append kek 100000 & ./bin/03-atomic-append kek 100000
 1055  [2025-06-11 22:10:26] ll
 1056  [2025-06-11 22:10:44] cmake --build build --target install && ./bin/03-atomic-append kek 100000 & ./bin/03-atomic-append kek 100000
 1057  [2025-06-11 22:10:47] ll
 1058  [2025-06-11 22:10:53] truncate kek
 1059  [2025-06-11 22:10:57] rm kek
 1060  [2025-06-11 22:11:00] cmake --build build --target install && ./bin/03-atomic-append kek 100000 & ./bin/03-atomic-append kek 100000
 1061  [2025-06-11 22:11:03] ll
 1062  [2025-06-11 22:11:07] rm kek
 1063  [2025-06-11 22:11:24] cmake --build build --target install && ./bin/03-atomic-append kek 100000 x & ./bin/03-atomic-append kek 100000 x
 1064  [2025-06-11 22:11:26] ll
 1065  [2025-06-11 22:11:37] cmake --build build --target install && ./bin/03-atomic-append kek 1000000 x & ./bin/03-atomic-append kek 1000000 x
 1066  [2025-06-11 22:11:44] ll
 1067  [2025-06-11 22:12:06] cmake --build build --target install && ./bin/03-atomic-append kek 1000000 x & ./bin/03-atomic-append kek 1000000 x
 1068  [2025-06-11 22:12:23] ll
 1069  [2025-06-11 22:12:38] ./bin/03-atomic-append kek 1000000 x & ./bin/03-atomic-append kek 1000000 x
 1070  [2025-06-11 22:12:43] ll
 1071  [2025-06-11 22:12:56] ./bin/03-atomic-append kek 10000000 x & ./bin/03-atomic-append kek 10000000 x
 1072  [2025-06-11 22:14:03] ll
 1073  [2025-06-11 23:20:56] ./bin/03-atomic-append kek 10000000 x & ./bin/03-atomic-append kek 10000000 x
 1074  [2025-06-11 23:21:46] ll
 1075  [2025-06-11 23:24:09] ./bin/03-atomic-append kek 10000 x & ./bin/03-atomic-append kek 10000 x
 1076  [2025-06-11 23:24:13] cmake --build build --target install
 1077  [2025-06-11 23:24:16] ./bin/03-atomic-append kek 10000 x & ./bin/03-atomic-append kek 10000 y
```
