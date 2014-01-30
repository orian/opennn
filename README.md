OpenNN library
======

This is a copy of http://sourceforge.net/projects/opennn/

##Prerequirements

One needs to install `libtinyxml` and `cmake 2.8`. On Ubuntu, it goes like that:

```
sudo apt-get install libtinyxml2-dev
sudo apt-get install cmake
sudo apt-get install g++
```

##Build and install
Then to build and install run:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make opennn
sudo make install
```

##Run tests
```
mkdir build
cd build
cmake -DWithTests=ON ..
make opennntests
cd ../tests/bin
../../build/bin/opennntests
```

##Examples

