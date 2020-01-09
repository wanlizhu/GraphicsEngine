#pragma once

#include "Wanlix/Utils/Macros.h"

namespace Wanlix
{
    enum class EDataType
    {
        Undefined = 0,
        Int8,
        Int16,
        Int32,
        Int64,
        Uint8,
        Uint16,
        Uint32,
        Uint64,
        Float16,
        Float32,
        Float64,
    };
    ENUM_CLASS_OPERATORS(EDataType)

    enum class EMessageBoxButton
    {
        None,
        Ok,
        Cancel,
        Retry,
        Abort,
        Ignore,
    };

    enum class EMessageBoxType
    {
        Ok,
        OkCancel,
        RetryCancel,
        AbortRetryIgnore,
    };

    enum class EFileEvent
    {
        Changed,
        Created,
        Deleted,
        Renamed,
    };
}