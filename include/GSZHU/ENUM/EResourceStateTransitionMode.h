#pragma once

#include <GSZHU/BasicTypes.h>

namespace GSZHU {
    enum ERESOURCE_STATE_TRANSITION_MODE : uint8_t {
        RESOURCE_STATE_TRANSITION_MODE_NONE = 0,
        RESOURCE_STATE_TRANSITION_MODE_TRANSITION,
        RESOURCE_STATE_TRANSITION_MODE_VERIFY
    };

}