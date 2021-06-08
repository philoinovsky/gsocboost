# Boost C++
## I. Basics
### A. Install (one-time)
```
git clone --recursive https://github.com/boostorg/boost.git
cd boost
git checkout develop
./bootstrap.sh
```
build python library only
```
./bootstrap.sh --with-libraries=python --with-python=/usr/bin/python3.8 --prefix=/home/philoy
```
### B. Build after made change
```
./b2 --install j8
```
### C. Compile cpp and run
```
g++ "onevent.cpp" -I/usr/include/python3.8 -I/home/philoy/boost -o k -L/home/philoy/boost/stage/lib -lboost_thread $(/usr/bin/python3.8-config --ldflags --embed) -fno-lto -lboost_python38 -lboost_system && ./k
```
## II. Advanced
add `.zshrc`, then run
`compile {file/path}`
to compile
