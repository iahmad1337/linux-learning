```bash
# configure
cmake -S . -B build --install-prefix=$(pwd) -G Ninja

# build + install
cmake --install build
```

Testing is manual:
```
  894  [2025-05-07 20:14:57] stat --format "size=%s blocks=%b block_size=%B" test-data/hole-02
  895  [2025-05-07 20:15:05] ./bin/make_hole -h 10 -o test-data/hole-10
  896  [2025-05-07 20:15:08] stat --format "size=%s blocks=%b block_size=%B" test-data/hole-10
  897  [2025-05-07 20:15:20] strace --syscall-times ./bin/cp test-data/hole-10 ./hole
  898  [2025-05-07 20:15:43] stat --format "size=%s blocks=%b block_size=%B" test-data/hole-10
  899  [2025-05-07 20:15:46] stat --format "size=%s blocks=%b block_size=%B" hole
  900  [2025-05-07 20:15:48] rm hole
  901  [2025-05-07 20:15:52] stat --format "size=%s blocks=%b block_size=%B" hole
  902  [2025-05-07 20:15:59] stat --format "size=%s blocks=%b block_size=%B" test-data/hole-10
  903  [2025-05-07 20:16:40] strace --syscall-times ./bin/cp test-data/hole-10 ./hole
  904  [2025-05-07 20:22:55] man lseek
  905  [2025-05-07 20:26:53] cmake --build build --target install
  906  [2025-05-07 20:26:56] strace --syscall-times ./bin/cp test-data/hole-10 ./hole
  907  [2025-05-07 20:27:18] cmp test-data/hole-10 ./hole && echo "SUCCESS" || echo "FAIL"
  908  [2025-05-07 20:27:29] rm hole
  909  [2025-05-07 20:27:35] ./bin/cp test-data/hole-10 ./hole
  910  [2025-05-07 20:27:37] cmp test-data/hole-10 ./hole && echo "SUCCESS" || echo "FAIL"
  911  [2025-05-07 20:27:45] stat --format "size=%s blocks=%b block_size=%B" test-data/hole-10
  912  [2025-05-07 20:27:49] stat --format "size=%s blocks=%b block_size=%B" hole
  913  [2025-05-07 20:28:12] ./bin/cp test-data/hole-50 ./hole
  914  [2025-05-07 20:28:17] stat --format "size=%s blocks=%b block_size=%B" hole
  915  [2025-05-07 20:28:23] stat --format "size=%s blocks=%b block_size=%B" test-data/hole-50
  916  [2025-05-07 20:28:42] ncdu
  917  [2025-05-07 20:29:19] cmake --build build --target install
  918  [2025-05-07 20:29:27] ./bin/cp test-data/hole-50 ./hole
  919  [2025-05-07 20:29:29] stat --format "size=%s blocks=%b block_size=%B" test-data/hole-50
  920  [2025-05-07 20:29:32] stat --format "size=%s blocks=%b block_size=%B" hole
  921  [2025-05-07 20:29:41] cmp test-data/hole-50 ./hole && echo "SUCCESS" || echo "FAIL"
```
