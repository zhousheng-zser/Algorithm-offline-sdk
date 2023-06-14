#include "common_protocols.hpp"

#include <g6/error_extensions.hpp>

namespace glasssix {
    void parser_result_status::ensure() const {
        if (code != 0) {
            throw source_code_aware_runtime_error{U8("Code"), code, U8("Message"), message};
        }
    }
} // namespace glasssix
