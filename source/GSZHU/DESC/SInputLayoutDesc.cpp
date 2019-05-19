#include <GSZHU/DESC/SInputLayoutDesc.h>

namespace GSZHU {
    SInputLayoutDesc::SInputLayoutDesc() noexcept
    {}

    SInputLayoutDesc(const SLayoutElement* _Elements, uint32_t _NumElements)
        : ElementArray(_Elements)
        , NumElements(_NumElements)
    {}

    bool SInputLayoutDesc::operator==(const SInputLayoutDesc& rhs) const {
        if (NumElements == rhs.NumElements) {
            for (int i = 0; i < NumElements; i++) {
                if (!(ElementArray[i] == rhs.ElementArray[i]))
                    return false;
            }
        }
        return true;
    }
}