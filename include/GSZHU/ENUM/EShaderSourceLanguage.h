#pragma once

#include <GSZHU/BasicTypes.h>

namespace GSZHU {
    enum ESHADER_SOURCE_LANGUAGE : uint32_t {
        SHADER_SOURCE_LANGUAGE_DEFAULT = 0,
        SHADER_SOURCE_LANGUAGE_HLSL,
        SHADER_SOURCE_LANGUAGE_GLSL
    };
}