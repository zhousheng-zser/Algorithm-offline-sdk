#pragma once

#include <vector>
#include "compat.hpp"

    class GX_API(DEMO) test {
    public:
        int add(int x,int y);
    };

extern "C" {
GX_API(DEMOC) int multiply(int x,int y);
}
