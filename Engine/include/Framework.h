#pragma once


#include "EngineConfig.h"
#ifdef GS_USE_D3D12
#include "RHI/D3D12/EngineD3D12.h"
#elif defined(GS_USE_VULKAN)
#include "RHI/Vulkan/EngineVulkan.h"
#elif defined(GS_USE_OPENGL)
#include "RHI/OpenGL/EngineOpenGL.h"
#else
#error Undefined GS backend. Make sure that a backend is selected in "EngineConfig.h"
#endif

#if NVAPI_ENABLED
#include <nvapi.h>
#pragma comment(lib, "nvapi64.lib")
#endif

#include <stdint.h>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include <ctime>
#include <unordered_map>
#include <Eigen/Eigen>
#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <glog/logging.h>

#ifndef arraysize
#define arraysize(a) (sizeof(a)/sizeof(a[0]))
#endif
#ifndef offsetof
#define offsetof(s, m) (size_t)( (ptrdiff_t)&reinterpret_cast<const volatile char&>((((s *)0)->m)) )
#endif

#ifdef _DEBUG
#define ASSERT(a)\
    if (!(a)) {\
        std::string str = "Assertion Failed(" + std::string(#a) + ")\n" +\
        "File " + __FILE__ + ", Line " + std::to_string(__LINE__);\
        LOG(FATAL) << str;\
    }

#define SHOULD_NOT_GET_HERE() ASSERT(false)
#else

#ifdef AUTOTEST 
#define ASSERT(a) if (!(a)) throw std::exception("Assertion Failed(" + std::string(#a) + ")\n")
#else
#define ASSERT(a) ((void)(a))
#endif

#ifdef _MSC_VER
#define SHOULD_NOT_GET_HERE() __assume(0)
#else
#define SHOULD_NOT_GET_HERE() __builtin_unreachable()
#endif

#endif

#define SAFE_DELETE(a) { delete a; a = nullptr; }
#define SAFE_DELETE_ARRAY(a) { delete[] a; a = nullptr; }
#define ALIGN_TO(align, val) (((val + align - 1) / align) * align)
#define CONCAT(a, b) a##b

#ifdef _MSC_VER
#define DEPRECATED(msg)  __declspec(deprecated(msg))
#define SUPPRESS_DEPRECATION  __pragma(warning(suppress : 4996));
#define FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define DEPRECATED(msg) __attribute__ ((deprecated(_msg_)))
#define SUPPRESS_DEPRECATION _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#define FORCEINLINE __attribute__((always_inline))
#endif




namespace GS
{
	using nanoseconds    = std::chrono::nanoseconds;
	using microseconds   = std::chrono::microseconds;
	using milliseconds   = std::chrono::milliseconds;
	using seconds        = std::chrono::seconds;
	using minutes        = std::chrono::minutes;
	using hours          = std::chrono::hours;
	using clock          = std::chrono::high_resolution_clock;
	template<typename _duration>
	using time_point     = std::chrono::time_point<clock, _duration>;
	using time_point_ns  = time_point<nanoseconds>;
	using time_point_mcs = time_point<microseconds>;
	using time_point_ms  = time_point<milliseconds>;
	using time_point_sec = time_point<seconds>;
	using time_point_min = time_point<minutes>;
	using time_point_h   = time_point<hours>;

	template<typename _time_point>
	constexpr std::time_t to_time_t(const _time_point& tp)
	{
		using _clock = typename _time_point::clock;
		return _clock::to_time_t(tp);
	}

	template<typename _duration1, typename _duration2>
	constexpr _duration1 duration_cast(const _duration2& du)
	{
		return std::chrono::duration_cast<_duration1>(du);
	}

	template<typename _tpoint1, typename _tpoint2>
	constexpr _tpoint1 time_point_cast(const _tpoint2& tp)
	{
		return std::chrono::time_point_cast<_tpoint1>(tp);
	}

	template<typename _tpoint>
	constexpr typename _tpoint::rep epoch_ms(const _tpoint& tp)
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
	}

	namespace fs = std::filesystem;

    enum class EShaderType 
    {
        Unknown = 0,
        Vertex,
        Pixel,
        Geometry,
        Hull,   // Tessellation Control
        Domain, // Tessellation Evaluation
        Compute,
#ifdef GS_USE_D3D12
        RayGeneration,
        Intersection,
        AnyHit,
        ClosestHit,
        Miss,
        Callable,
#endif
        COUNT
    };

    enum class EShadingLanguage
    {
        Unknown = 0,
        GLSL,
        VulkanGLSL,
        HLSL,
        Slang,
    };

    enum class EAttachmentType
    {
        None = 0,
        Color = 1,
        Depth = 2,
        Stencil = 4,
        All = Color | Depth | Stencil
    };
    ENUM_CLASS_OPERATORS(EAttachmentType)

    enum class EComparisonFunc 
    {
        Disabled = 0,
        Never,
        Always,
        Less,
        Equal,
        NotEqual,
        LessEqual,
        Greater,
        GreaterEqual,
    };

    template<typename T>
    inline T clamp(const T& val, const T& minVal, const T& maxVal)
    {
        return std::min(std::max(val, minVal), maxVal);
    }

    template<typename T>
    inline bool is_power_of_2(T a) 
    {
        uint64_t tmp = (uint64_t)a;
        return (tmp & (tmp - 1)) == 0;
    }

    template<typename BASE, typename DERIVED>
    class inherit_shared_from_this
    {
    public:
        std::shared_ptr<DERIVED> shared_from_this()
        {
            BASE* base = static_cast<DERIVED*>(this);
            std::shared_ptr<BASE> shared = base->shared_from_this();
            return std::static_pointer_cast<DERIVED>(shared);
        }

        std::shared_ptr<const DERIVED> shared_from_this() const
        {
            const BASE* base = static_cast<const DERIVED*>(this);
            std::shared_ptr<const BASE> shared = base->shared_from_this();
            return std::static_pointer_cast<const DERIVED>(shared);
        }
    };


    inline std::string to_string(EShaderType type) 
    {
        switch(type)
        {
        case EShaderType::Vertex:
            return "Vertex";
        case EShaderType::Pixel:
            return "Pixel";
        case EShaderType::Geometry:
            return "Geometry";
        case EShaderType::Hull:
            return "Hull";
        case EShaderType::Domain:
            return "Domain";
        case EShaderType::Compute:
            return "Compute";
#ifdef GS_USE_D3D12
        case EShaderType::RayGeneration:
            return "RayGeneration";
        case EShaderType::Intersection:
            return "Intersection";
        case EShaderType::AnyHit:
            return "AnyHit";
        case EShaderType::ClosestHit:
            return "ClosestHit";
        case EShaderType::Miss:
            return "Miss";
        case EShaderType::Callable:
            return "Callable";
#endif
        default:
            SHOULD_NOT_GET_HERE();
            return "";
        }
    }

    inline std::string to_string(EComparisonFunc func)
    {
        switch(func)
        {
        case EComparisonFunc::Disabled:
            return "Disabled";
        case EComparisonFunc::Always:
            return "Always";
        case EComparisonFunc::Never:
            return "Never";
        case EComparisonFunc::Less:
            return "Less";
        case EComparisonFunc::Equal:
            return "Equal";
        case EComparisonFunc::NotEqual:
            return "NotEqual";
        case EComparisonFunc::LessEqual:
            return "LessEqual";
        case EComparisonFunc::Greater:
            return "Greater";
        case EComparisonFunc::GreaterEqual:
            return "GreaterEqual";
        default:
            SHOULD_NOT_GET_HERE();
			return "";
        }
    }
}