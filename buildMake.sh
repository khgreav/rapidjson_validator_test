rm -rf build && mkdir build
cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=Debug
cmake --build build
