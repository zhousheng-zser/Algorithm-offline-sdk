#include "distance.hpp"

#include <cmath>
#include <stdexcept>

namespace glasssix {
        float distance_l2::compare(const float* a, const float* b, uint32_t size) {
            float result = 0;
            float diff0, diff1, diff2, diff3;
            const float* last         = a + size;
            const float* unroll_group = last - 3;

            /* Process 4 items with each loop for efficiency. */
            while (a < unroll_group) {
                diff0 = a[0] - b[0];
                diff1 = a[1] - b[1];
                diff2 = a[2] - b[2];
                diff3 = a[3] - b[3];
                result += diff0 * diff0 + diff1 * diff1 + diff2 * diff2 + diff3 * diff3;
                a += 4;
                b += 4;
            }
            /* Process last 0-3 pixels.  Not needed for standard vector lengths. */
            while (a < last) {
                diff0 = *a++ - *b++;
                result += diff0 * diff0;
            }

            if (!std::isfinite(result)) {
                throw std::runtime_error("infinite number");
            }

            return result;
        }

        float distance_inner_product::compare(const float* a, const float* b, uint32_t size) {
            float result = 0;
            float dot0, dot1, dot2, dot3;
            const float* last         = a + size;
            const float* unroll_group = last - 3;

            /* Process 4 items with each loop for efficiency. */
            while (a < unroll_group) {
                dot0 = a[0] * b[0];
                dot1 = a[1] * b[1];
                dot2 = a[2] * b[2];
                dot3 = a[3] * b[3];
                result += dot0 + dot1 + dot2 + dot3;
                a += 4;
                b += 4;
            }
            /* Process last 0-3 pixels.  Not needed for standard vector lengths. */
            while (a < last) {
                result += *a++ * *b++;
            }

            if (!std::isfinite(result)) {
                throw std::runtime_error("infinite number");
            }

            return result;
        }

        float distance_fast_l2::norm(const float* a, uint32_t size) {
            float result = 0;
            float dot0, dot1, dot2, dot3;
            const float* last         = a + size;
            const float* unroll_group = last - 3;

            /* Process 4 items with each loop for efficiency. */
            while (a < unroll_group) {
                dot0 = a[0] * a[0];
                dot1 = a[1] * a[1];
                dot2 = a[2] * a[2];
                dot3 = a[3] * a[3];
                result += dot0 + dot1 + dot2 + dot3;
                a += 4;
            }
            /* Process last 0-3 pixels.  Not needed for standard vector lengths. */
            while (a < last) {
                result += (*a) * (*a);
                a++;
            }

            if (!std::isfinite(result)) {
                throw std::runtime_error("infinite number");
            } else if (fabsf(result) < 1e-5) {
                throw std::runtime_error("zero vector");
            }

            return result;
        }

        float distance_fast_l2::compare(const float* a, float norma, const float* b, float normb, uint32_t size) {
            float result = -2 * distance_inner_product::compare(a, b, size);
            result       = result + norma + normb; //(a-b)*(a-b)=a^2 + b^2 - 2*a*b

            if (!std::isfinite(result)) {
                throw std::runtime_error("infinite number");
            }

            return result;
        }

        float distance_cosine::norm(const float* a, uint32_t size) {
            float result = 0;
            float dot0, dot1, dot2, dot3;
            const float* last         = a + size;
            const float* unroll_group = last - 3;

            /* Process 4 items with each loop for efficiency. */
            while (a < unroll_group) {
                dot0 = a[0] * a[0];
                dot1 = a[1] * a[1];
                dot2 = a[2] * a[2];
                dot3 = a[3] * a[3];
                result += dot0 + dot1 + dot2 + dot3;
                a += 4;
            }
            /* Process last 0-3 pixels.  Not needed for standard vector lengths. */
            while (a < last) {
                result += (*a) * (*a);
                a++;
            }

            result = sqrt(result);

            if (!std::isfinite(result)) {
                throw std::runtime_error{"infinite number"};
            } else if (fabsf(result) < 1e-5) {
                throw std::runtime_error{"zero vector"};
            }

            return result;
        }

        float distance_cosine::compare(const float* a, float norma, const float* b, float normb, uint32_t size) {
            float result = distance_inner_product::compare(a, b, size);
            result       = result / (norma * normb);
            result       = 1 - result; // more similar, distance should be closer, so we add minus before result

            if (!std::isfinite(result)) {
                throw std::runtime_error{"infinite number"};
            }

            return result;
        }
} // namespace glasssix
