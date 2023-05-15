#pragma once

// Directives for imports and exports are platform-specific not compiler-specific,
// so use WIN32 instead of _MSC_VER here to make it behave correctly and expectedly.
#ifdef _WIN32
#define GX_IMPORT __declspec(dllimport)
#define GX_EXPORT __declspec(dllexport)
#else
#define GX_IMPORT
#define GX_EXPORT __attribute__((visibility("default")))
#endif

#define GX_CONDITIONAL_COMMA_1       ,
#define GX_CONDITIONAL_COMMA_IMPL(x) GX_CONDITIONAL_COMMA_##x
#define GX_CONDITIONAL_COMMA(x)      GX_CONDITIONAL_COMMA_IMPL(x)

#define GX_SELECT_THIRD_ARGUMENT(a, b, c, ...) c
#define GX_CONDITIONAL(condition, consequent, alternate) \
    GX_SELECT_THIRD_ARGUMENT(GX_CONDITIONAL_COMMA(condition), consequent, alternate)
#define GX_API(x) GX_CONDITIONAL(GX_IS_##x##_IMPL, GX_IMPORT, GX_EXPORT)

#if __cplusplus >= 202002L
#define GX_HAS_CXX20 1
#else
#define GX_HAS_CXX20 0
#endif

#if defined(__GUNC__) || defined(__clang__)
#define GX_KEEP_ALIVE __attribute__((used))
#else
#define GX_KEEP_ALIVE
#endif
