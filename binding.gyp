{
    "targets": [
        {
            "target_name": "dserial",
            "sources": [
                "src/binding.cpp",
                "src/dserial.cpp"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
            ],
            'dependencies': [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "defines": [ "NAPI_CPP_EXCEPTIONS" ],
            "defines": [
                "NAPI_VERSION=<(napi_build_version)"
            ],
            "msvs_settings": {
                "VCLinkerTool": {
                    "SetChecksum": "true"
                },
                "VCCLCompilerTool": {
                    "ExceptionHandling": 1,
                    "AdditionalOptions": [
                        "/EHsc"
                    ]
                }
            },
        }

    ]
}
