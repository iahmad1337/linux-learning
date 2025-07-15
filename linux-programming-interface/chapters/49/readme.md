# Testing
```
 1371  [2025-07-14 21:38:31] dd if=/dev/urandom of=./49/one-page.rnd bs=4096 count=1
 1372  [2025-07-14 21:38:45] dd if=/dev/urandom of=./49/two-page.rnd bs=4096 count=w
 1373  [2025-07-14 21:38:58] dd if=/dev/urandom of=./49/two-page.rnd bs=4096 count=2
 1374  [2025-07-14 21:40:11] dd if=/dev/urandom of=./49/two-page-plus.rnd bs=4100 count=2
 1375  [2025-07-14 21:40:36] cd 49
 1376  [2025-07-14 21:40:40] mv *rnd test
 1379  [2025-07-14 22:07:16] cmake --build build --target install
 1380  [2025-07-14 22:07:18] cd ..
 1381  [2025-07-14 22:07:20] cmake --build build --target install
 1382  [2025-07-14 22:07:43] (cd 49/test/; ./do-test)
 1395  [2025-07-14 22:25:05] hexdump -C -n100 49/test/one-page.rnd
 1396  [2025-07-14 22:25:13] hexdump -C -n100 49/test/one-page.rnd.copy
 1397  [2025-07-14 22:26:02] cmake --build build --target install && (cd 49/test/; ./do-test)
```
