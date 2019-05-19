#pragma once

#include <GSZHU/BasicTypes.h>

namespace GSZHU {
    struct SMappedTextureSubresource {
        void* Data = nullptr;
        uint32_t Stride = 0;
        uint32_t DepthStride = 0;
    };
}