#pragma once
#include <string>
#include <vector>

#include <g6/char8_t_remediation.hpp>
#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>

namespace glasssix::face {
    struct baz {
        GX_BEGIN_FIELDS(baz);
        GX_FIELD(int, a);
        GX_FIELD(std::string, b);
        GX_FIELD(std::vector<int>, c);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE_DEFAULT;
    };

    void foo() {
        constexpr auto xstr = U8("123");
        const char* x       = xstr;

        auto str      = glasssix::format("Hello {}{}", 123, xstr);
        auto&& logger = glasssix::get_screen_logger();

        logger.line(U8("Hello"));
        logger.json(glasssix::json(baz{.a{123}, .b{U8("hello")}, .c{1, 2, 3, 4, 5}}));
        glasssix::json j;

        auto value = j.get<baz>();
    }
} // namespace glasssix::face
