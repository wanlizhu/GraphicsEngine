#pragma once
#include <ZHUENGINE/Core/Config.h>
#include <memory>

namespace ZHU
{
    template<typename... ARGS>
    class IObserver
    {
    public:
        virtual void Update(ARGS... args) = 0;
    };
}