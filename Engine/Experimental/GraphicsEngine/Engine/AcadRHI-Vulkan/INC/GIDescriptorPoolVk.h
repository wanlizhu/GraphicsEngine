#pragma once

#include "GIDescriptorSetVk.h"

namespace AutoCAD::Graphics::Engine
{
    class GIShaderReflectionVk;
    class GIDescriptorSetVk;

    /*
     * Regardless of whether sets are individually freed by calling vkFreeDescriptorSets() or freed
     * in bulk by calling vkResetDescriptorPool(), care must be taken to ensure that sets are not
     * referenced after they have been freed. In particular, any command buffer containing commands that
     * might reference descriptor sets that are to be freed should either have completed execution or should
     * be discarded without submission.
    */
    class GIDescriptorPoolVk : public GIDeviceObjectVk
    {
        DECL_DEVICE_OBJECT(GIDescriptorPoolVk)
    public:
        static SharedPtr<GIDescriptorPoolVk> Create(
            SharedPtr<GIDeviceVk> device,
            SharedPtr<GIShaderReflectionVk> reflection,
            uint32_t maxSets,
            const std::vector<VkDescriptorPoolSize>& poolSizes
        );

        virtual ~GIDescriptorPoolVk();
        virtual bool IsValid() const override final;
        virtual void SetDebugName(const char* name) const override final;
        virtual void SetDebugTag(const DebugTag& tag) const override final;

        operator const VkDescriptorPool& () const;
        std::thread::id GetThreadId() const;
        SharedPtr<GIDescriptorSetVk> Allocate(
            SharedPtr<GIDescriptorSetLayoutVk> setLayout, 
            SharedPtr<GIDescriptorSetVk> parent
        );
        
    protected:
        GIDescriptorPoolVk(SharedPtr<GIDeviceVk> device);

    private:
        VkDescriptorPool mDescriptorPoolHandle = VK_NULL_HANDLE;
        SharedPtr<GIShaderReflectionVk> mReflection;
        std::thread::id mThreadId;
    };
}