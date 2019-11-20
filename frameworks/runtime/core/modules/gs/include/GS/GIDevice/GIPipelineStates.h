#pragma once

#include "DeviceObject.h"
#include <array>

namespace GS
{
    enum class EStateType
    {
        Viewport,
        Scissor,
        Rasterization,
        Multisample,
        DepthStencil,
        ColorBlend,
    };

    enum class EPolygonMode
    {
        Fill,
        Line,
        Point,
    };

    enum class ECullMode
    {
        None,
        Front,
        Back,
        Both,
    };

    enum class ECompareOp
    {
        Never,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always,
    };

    enum class EStencilOp
    {
        Keep,
        Zero,
        Replace,
        IncrementAndClamp,
        DecrementAndClamp,
        Invert,
        IncrementAndWarp,
        DecrementAndWarp,
    };

    enum class EBlendFactor
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        DstColor,
        OneMinusDstColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
        ConstantColor,
        OneMinusConstantColor,
        ConstantAlpha,
        OneMinusConstantAlpha,
        SrcAlphaSaturate,
        Src1Color,
        OneMinusSrc1Color,
        Src1Alpha,
        OneMinusSrc1Alpha,
    };

    enum class EBlendOp
    {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max,
    };

    enum class ELogicOp
    {
		Clear,
		And,
		AndReverse,
		Copy,
		AndInverted,
		NoOp,
		Xor,
		Or,
		Nor,
		Equivalent,
		Invert,
		OrReverse,
		CopyInverted,
		OrInverted,
		Nand,
		Set,
    };

    class StateBase : public DeviceObject
    {
    public:
        using Ptr = std::shared_ptr<StateBase>;

        StateBase(const std::string& name, GIDevice::Ptr device, EStateType type)
            : DeviceObject(name, device)
            , mType(type)
        {}

        virtual void Flush() = 0;

        inline void SetDirty() { mStateDirty = true; }
        inline void SetDynamic(bool enabled = true) { mDynamicState = enabled; }
        inline bool IsDirty() const { return mStateDirty; }
        inline bool IsDynamic() const { return mDynamicState; }

    protected:
        EStateType mType;
        bool mStateDirty = false;
        bool mDynamicState = false;
    };

    class ViewportState final : public StateBase
    {
    public:
        using Ptr = std::shared_ptr<ViewportState>;

        ViewportState(const std::string& name, GIDevice::Ptr device)
            : StateBase(name, device, EStateType::Viewport)
        {}

        virtual void Init() override;
        virtual void Destroy() override;
        virtual void Flush() override;
        bool IsFullframe() const;

    public:
        Region region;
        float minDepth = 0.0f;
        float maxDepth = 1.0f;
    };

    class ScissorState final : public StateBase
    {
    public:
        using Ptr = std::shared_ptr<ScissorState>;

        ScissorState(const std::string& name, GIDevice::Ptr device)
            : StateBase(name, device, EStateType::Scissor)
        {}

        virtual void Init() override;
        virtual void Destroy() override;
        virtual void Flush() override;
        bool IsFullframe() const;

    public:
        Region region;
    };

    class RasterizationState final : public StateBase
    {
    public:
        using Ptr = std::shared_ptr<RasterizationState>;

        RasterizationState(const std::string& name, GIDevice::Ptr device)
            : StateBase(name, device, EStateType::Scissor)
        {}

        virtual void Init() override;
        virtual void Destroy() override;
        virtual void Flush() override;

    public:
        bool         depthClampEnable = false;
        bool         rasterizerDiscardEnable = false;
        EPolygonMode polygonMode = EPolygonMode::Fill;
        float        lineWidth = 1.0f;
        ECullMode    cullMode = ECullMode::None;
        bool         frontFaceCCW = true;
        bool         depthBiasEnable = false;
        float        depthBiasConstantFactor = 0.0f;
        float        depthBiasClamp = 0.0f;
        float        depthBiasSlopeFactor = 0.0f;
    };

    class MultisampleState final : public StateBase
    {
    public:
        using Ptr = std::shared_ptr<MultisampleState>;

        MultisampleState(const std::string& name, GIDevice::Ptr device)
            : StateBase(name, device, EStateType::Multisample)
        {}

        virtual void Init() override;
        virtual void Destroy() override;
        virtual void Flush() override;

    public:
        bool     sampleShadingEnable = false;
        int      rasterizationSamples = 1;
        float    minSampleShading = 1.0f;
        uint32_t sampleMask = 0;
        bool     alphaToCoverageEnable = false;
        bool     alphaToOneEnable = false;
    };

    class DepthStencilState final : public StateBase
    {
    public:
        using Ptr = std::shared_ptr<DepthStencilState>;
        struct StencilDesc
        {
            EStencilOp failOp = EStencilOp::Keep;
            EStencilOp passOp = EStencilOp::Keep;
            EStencilOp depthFailOp = EStencilOp::Keep;
            ECompareOp compareOp = ECompareOp::Always;
            uint32_t compareMask = 0;
            uint32_t writeMask = 0;
            uint32_t reference = 0;
        };

        DepthStencilState(const std::string& name, GIDevice::Ptr device)
            : StateBase(name, device, EStateType::DepthStencil)
        {}

        virtual void Init() override;
        virtual void Destroy() override;
        virtual void Flush() override;

    public:
        bool        depthTestEnable = false;
        bool        depthWriteEnable = false;
        ECompareOp  depthCompareOp = ECompareOp::Always;
        bool        depthBoundsTestEnable = false;

        bool        stencilTestEnable = false;
        StencilDesc front;
        StencilDesc back;
        float       minDepthBounds = 0.0f;
        float       maxDepthBounds = 1.0f;
    };

    class ColorBlendAttachmentState
    {
        bool blendEnable = false;

        EBlendFactor srcColorBlendFactor;
        EBlendFactor dstColorBlendFactor;
        EBlendOp     colorBlendOp;

        EBlendFactor srcAlphaBlendFactor;
        EBlendFactor dstAlphaBlendFactor;
        EBlendOp     alphaBlendOp;
    };

    class ColorBlendState final : public StateBase
    {
    public:
        using Ptr = std::shared_ptr<ColorBlendState>;

        ColorBlendState(const std::string& name, GIDevice::Ptr device)
            : StateBase(name, device, EStateType::ColorBlend)
        {}

        virtual void Init() override;
        virtual void Destroy() override;
        virtual void Flush() override;

    public:
        bool                 logicOpEnable = false;
        ELogicOp             logicOp = ELogicOp::Copy;
        std::array<float, 4> blendConstants{ 0.0f };
        std::vector<ColorBlendAttachmentState> attachmentStates;
    };
}