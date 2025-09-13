#include <napi.h>
#include "dserial.h"

using namespace std;

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "serial"),
                Napi::Function::New(env, Serial));

    return exports;
}

NODE_API_MODULE(dserial, Init) 