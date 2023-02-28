#!/bin/sh
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../cmake/RV1109Toolchain.cmake -DGX_TOOLCHAIN_PREFIX=/home/zser/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin/arm-linux-gnueabihf- -DCMAKE_INSTALL_PREFIX=/home/zser/tool -DGX_MISCELLANEOUS_ROOT=/home/zser/install/miscellaneous -DGX_GTEST_ROOT=/home/zser/install/googletest
