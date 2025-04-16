```bash
# configure
cmake -S . -B build --install-prefix=$(pwd) -G Ninja

# build + install
cmake --install build
```
