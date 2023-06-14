#pragma once
#include <cstdint>

namespace glasssix {
        struct distance_l2 {
            static float compare(const float* a, const float* b, uint32_t size);
        };

        struct distance_inner_product {
            static float compare(const float* a, const float* b, uint32_t size);
        };

        struct distance_fast_l2 : public distance_inner_product {
            static float norm(const float* a, uint32_t size);
            static float compare(const float* a, float norma, const float* b, float normb, uint32_t size);
        };


        struct distance_cosine : public distance_inner_product {
            static float norm(const float* a, uint32_t size);
            static float compare(const float* a, float norma, const float* b, float normb, uint32_t size);
        };
} // namespace glasssix
