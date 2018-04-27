# OPENCC - CMAKE Builder


## Please do the following change to the original OPEN64 files

- Copy osprey/linux to osprey/macos
- Extract the files from utils/changed.tar.gz into the open64 dir.
- Cheers!

## 1. Make sure you are in the opencc_cmake dir , then run :

```Shell
nginx@opencc_cmake$ mkdir cmake-build-debug
nginx@opencc_cmake$ cd cmake-build-debug
nginx@opencc_cmake$ cmake ..
nginx@opencc_cmake$ make
```


## 2. Partial building
- Should you want to build a part of it, rather than the whole project, just simply
```
 cmake ..  --> cmake ../MODULE_NAME

e.g.  cmake ../irtools


## 3. Miselleneous