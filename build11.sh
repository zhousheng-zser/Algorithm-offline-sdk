#!/bin/sh
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../cmake/RV1109Toolchain.cmake -DGX_TOOLCHAIN_PREFIX=/home/zser/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf- -DCMAKE_INSTALL_PREFIX=/home/zser/tool -DGX_MISCELLANEOUS_ROOT=/home/zser/install/miscellaneous -DGX_GTEST_ROOT=/home/zser/install/googletest
