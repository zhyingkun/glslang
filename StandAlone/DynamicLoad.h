#pragma once

#if defined(_WIN32)

#include <windows.h>

typedef struct {
    HMODULE handle;
    char* errmsg;
} uv_lib_t;

#elif defined(__APPLE__) || defined(__linux__)

typedef struct {
    void* handle;
    char* errmsg;
} uv_lib_t;

#endif

#define UV_EXTERN

UV_EXTERN int uv_dlopen(const char* filename, uv_lib_t* lib);
UV_EXTERN void uv_dlclose(uv_lib_t* lib);
UV_EXTERN int uv_dlsym(uv_lib_t* lib, const char* name, void** ptr);
UV_EXTERN const char* uv_dlerror(const uv_lib_t* lib);

class DynamicLoad {
public:
    DynamicLoad(const char* fileName);
    ~DynamicLoad();

    DynamicLoad(DynamicLoad&) = delete;
    DynamicLoad& operator=(DynamicLoad&) = delete;

    DynamicLoad(DynamicLoad&& other) noexcept;
    DynamicLoad& operator=(DynamicLoad&& other) noexcept;

    template <typename T> T FindFunctionSymbol(const char* name);

protected:
    void Swap(DynamicLoad* a, DynamicLoad* b);

private:
    uv_lib_t lib;
};
