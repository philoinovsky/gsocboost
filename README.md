```
g++ hello.cpp -I /usr/include/python3.8 -I /home/philoy/boost -L /home/philoy/boost/stage/lib -shared -fPIC -o hello.so
./bootstrap.sh --with-libraries=python --with-python=/usr/bin/python3.8 --prefix=/home/philoy
./b2 --install -j8


g++ "#eventtest3.cpp" -I /home/philoy/boost -pthread -o k -lboost_thread && ./k
./bootstrap.sh --with-libraries=python --with-python=/usr/bin/python3.8 --prefix=/home/philoy && ./b2 --install -j8

g++ "onevent.cpp" -I /usr/include/python3.8 -I /home/philoy/boost -L /home/philoy/boost/stage/lib -o k -lboost_thread && ./k

g++ "onevent.cpp" -I/usr/include/python3.8 -I/home/philoy/boost -o k -L/home/philoy/boost/stage/lib -lboost_thread $(/usr/bin/python3.8-config --ldflags --embed) -fno-lto -lboost_python38 -lboost_system && ./k

g++ "#eventtest4.cpp" -I/usr/include/python3.8 -I/home/philoy/boost -o k -L/home/philoy/boost/stage/lib -lboost_thread $(/usr/bin/python3.8-config --ldflags --embed) -fno-lto -lboost_python38 -lboost_system && ./k
```
