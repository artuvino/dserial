#ifndef DSERIAL_H
#define DSERIAL_H

#include <napi.h>
#include <string>
#include <cmath>

// Windows-specific includes
#ifdef _WIN32
    #include <windows.h>
    #include <winioctl.h>
#endif

using namespace std;

Napi::Value Serial(const Napi::CallbackInfo& info);

#endif