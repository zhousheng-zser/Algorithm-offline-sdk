#if !(GX_IS_GXOFFLINERECOGNITION_IMPL)
#pragma push_macro("GX_IDENTITY")
#pragma push_macro("GX_BEGIN_FIELDS")
#pragma push_macro("GX_FIELD")
#pragma push_macro("GX_END_FIELDS")
#pragma push_macro("GX_JSON_SERIALIZABLE")
#pragma push_macro("GX_JSON_SERIALIZABLE_DEFAULT")

#undef GX_IDENTITY
#undef GX_BEGIN_FIELDS
#undef GX_FIELD
#undef GX_END_FIELDS
#undef GX_JSON_SERIALIZABLE
#undef GX_JSON_SERIALIZABLE_DEFAULT

#define GX_IDENTITY(...) decltype(static_cast<__VA_ARGS__(*)()>(nullptr)())
#define GX_BEGIN_FIELDS(type)
#define GX_FIELD(type, name) type name{}
#define GX_END_FIELDS
#define GX_JSON_SERIALIZABLE(name)
#define GX_JSON_SERIALIZABLE_DEFAULT
#endif
