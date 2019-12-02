#include "Wanlix/Core3D/Graphics/Format.h"
#include <tuple>

namespace Wanlix
{
    // Shortcuts for the format flags
    static const uint32_t Depth = FormatFlags::HasDepth;
    static const uint32_t Stencil = FormatFlags::HasStencil;
    static const uint32_t sRGB = FormatFlags::IsColorSpace_sRGB;
    static const uint32_t Compr = FormatFlags::IsCompressed;
    static const uint32_t Norm = FormatFlags::IsNormalized;
    static const uint32_t Integer = FormatFlags::IsInteger;
    static const uint32_t Unsigned = FormatFlags::IsUnsigned;
    static const uint32_t Packed = FormatFlags::IsPacked;
    static const uint32_t RTV = FormatFlags::SupportsRenderTarget;
    static const uint32_t Mips = FormatFlags::SupportsMips;
    static const uint32_t GenMips = FormatFlags::SupportsGenerateMips | Mips | RTV;
    static const uint32_t Dim1D = FormatFlags::SupportsTexture1D;
    static const uint32_t Dim2D = FormatFlags::SupportsTexture2D;
    static const uint32_t Dim3D = FormatFlags::SupportsTexture3D;
    static const uint32_t DimCube = FormatFlags::SupportsTextureCube;
    static const uint32_t Vertex = FormatFlags::SupportsVertex;

    static const uint32_t Dim1D_2D = Dim1D | Dim2D;
    static const uint32_t Dim2D_3D = Dim2D | Dim3D;
    static const uint32_t Dim1D_2D_3D = Dim1D | Dim2D | Dim3D;
    static const uint32_t UInt = Integer | Unsigned;
    static const uint32_t SInt = Integer;
    static const uint32_t UNorm = UInt | Norm;
    static const uint32_t SNorm = SInt | Norm;
    static const uint32_t SFloat = Unsigned;
    static const uint32_t UFloat = 0;

    // Declaration of all hardware format descriptors
    static const FormatAttributes g_formatAttribs[] =
    {
        //   bits  w  h  c  format                   dataType
        {   0, 0, 0, 0, ColorFormat::R,            DataType::Undefined, 0                                                          }, // Undefined

        /* --- Alpha channel color formats --- */
        //   bits  w  h  c  format                   dataType
        {   8, 1, 1, 1, ColorFormat::Alpha,        DataType::UInt8,     GenMips | Dim1D_2D_3D | DimCube | UNorm                    }, // A8UNorm

        /* --- Red channel color formats --- */
        //   bits  w  h  c  format                   dataType
        {   8, 1, 1, 1, ColorFormat::R,            DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // R8UNorm
        {   8, 1, 1, 1, ColorFormat::R,            DataType::Int8,      Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // R8SNorm
        {   8, 1, 1, 1, ColorFormat::R,            DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // R8UInt
        {   8, 1, 1, 1, ColorFormat::R,            DataType::Int8,      Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // R8SInt

        {  16, 1, 1, 1, ColorFormat::R,            DataType::UInt16,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // R16UNorm
        {  16, 1, 1, 1, ColorFormat::R,            DataType::Int16,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SNorm           }, // R16SNorm
        {  16, 1, 1, 1, ColorFormat::R,            DataType::UInt16,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // R16UInt
        {  16, 1, 1, 1, ColorFormat::R,            DataType::Int16,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // R16SInt
        {  16, 1, 1, 1, ColorFormat::R,            DataType::Float16,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // R16Float

        {  32, 1, 1, 1, ColorFormat::R,            DataType::UInt32,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // R32UInt
        {  32, 1, 1, 1, ColorFormat::R,            DataType::Int32,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // R32SInt
        {  32, 1, 1, 1, ColorFormat::R,            DataType::Float32,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // R32Float

        {  64, 1, 1, 1, ColorFormat::R,            DataType::Float64,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // R64Float

        /* --- RG color formats --- */
        //   bits  w  h  c  format                   dataType
        {  16, 1, 1, 2, ColorFormat::RG,           DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // RG8UNorm
        {  16, 1, 1, 2, ColorFormat::RG,           DataType::Int8,      Vertex | GenMips | Dim1D_2D_3D | DimCube | SNorm           }, // RG8SNorm
        {  16, 1, 1, 2, ColorFormat::RG,           DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RG8UInt
        {  16, 1, 1, 2, ColorFormat::RG,           DataType::Int8,      Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RG8SInt

        {  32, 1, 1, 2, ColorFormat::RG,           DataType::UInt16,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // RG16UNorm
        {  32, 1, 1, 2, ColorFormat::RG,           DataType::Int16,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SNorm           }, // RG16SNorm
        {  32, 1, 1, 2, ColorFormat::RG,           DataType::UInt16,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RG16UInt
        {  32, 1, 1, 2, ColorFormat::RG,           DataType::Int16,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RG16SInt
        {  32, 1, 1, 2, ColorFormat::RG,           DataType::Float16,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RG16Float

        {  64, 1, 1, 2, ColorFormat::RG,           DataType::UInt32,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RG32UInt
        {  64, 1, 1, 2, ColorFormat::RG,           DataType::Int32,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RG32SInt
        {  64, 1, 1, 2, ColorFormat::RG,           DataType::Float32,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RG32Float

        { 128, 1, 1, 2, ColorFormat::RG,           DataType::Float64,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RG64Float

        /* --- RGB color formats --- */
        //   bits  w  h  c  format                   dataType
        {  24, 1, 1, 3, ColorFormat::RGB,          DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // RGB8UNorm
        {  24, 1, 1, 3, ColorFormat::RGB,          DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm | sRGB    }, // RGB8UNorm_sRGB
        {  24, 1, 1, 3, ColorFormat::RGB,          DataType::Int8,      Vertex | GenMips | Dim1D_2D_3D | DimCube | SNorm           }, // RGB8SNorm
        {  24, 1, 1, 3, ColorFormat::RGB,          DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RGB8UInt
        {  24, 1, 1, 3, ColorFormat::RGB,          DataType::Int8,      Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RGB8SInt

        {  48, 1, 1, 3, ColorFormat::RGB,          DataType::UInt16,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // RGB16UNorm
        {  48, 1, 1, 3, ColorFormat::RGB,          DataType::Int16,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SNorm           }, // RGB16SNorm
        {  48, 1, 1, 3, ColorFormat::RGB,          DataType::UInt16,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RGB16UInt
        {  48, 1, 1, 3, ColorFormat::RGB,          DataType::Int16,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RGB16SInt
        {  48, 1, 1, 3, ColorFormat::RGB,          DataType::Float16,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RGB16Float

        {  96, 1, 1, 3, ColorFormat::RGB,          DataType::UInt32,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RGB32UInt
        {  96, 1, 1, 3, ColorFormat::RGB,          DataType::Int32,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RGB32SInt
        {  96, 1, 1, 3, ColorFormat::RGB,          DataType::Float32,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RGB32Float

        { 192, 1, 1, 3, ColorFormat::RGB,          DataType::Float64,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RGB64Float

        /* --- RGBA color formats --- */
        //   bits  w  h  c  format                   dataType
        {  32, 1, 1, 4, ColorFormat::RGBA,         DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // RGBA8UNorm
        {  32, 1, 1, 4, ColorFormat::RGBA,         DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm | sRGB    }, // RGBA8UNorm_sRGB
        {  32, 1, 1, 4, ColorFormat::RGBA,         DataType::Int8,      Vertex | GenMips | Dim1D_2D_3D | DimCube | SNorm           }, // RGBA8SNorm
        {  32, 1, 1, 4, ColorFormat::RGBA,         DataType::UInt8,     Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RGBA8UInt
        {  32, 1, 1, 4, ColorFormat::RGBA,         DataType::Int8,      Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RGBA8SInt

        {  64, 1, 1, 4, ColorFormat::RGBA,         DataType::UInt16,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UNorm           }, // RGBA16UNorm
        {  64, 1, 1, 4, ColorFormat::RGBA,         DataType::Int16,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SNorm           }, // RGBA16SNorm
        {  64, 1, 1, 4, ColorFormat::RGBA,         DataType::UInt16,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RGBA16UInt
        {  64, 1, 1, 4, ColorFormat::RGBA,         DataType::Int16,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RGBA16SInt
        {  64, 1, 1, 4, ColorFormat::RGBA,         DataType::Float16,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RGBA16Float

        { 128, 1, 1, 4, ColorFormat::RGBA,         DataType::UInt32,    Vertex | GenMips | Dim1D_2D_3D | DimCube | UInt            }, // RGBA32UInt
        { 128, 1, 1, 4, ColorFormat::RGBA,         DataType::Int32,     Vertex | GenMips | Dim1D_2D_3D | DimCube | SInt            }, // RGBA32SInt
        { 128, 1, 1, 4, ColorFormat::RGBA,         DataType::Float32,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RGBA32Float

        { 256, 1, 1, 4, ColorFormat::RGBA,         DataType::Float64,   Vertex | GenMips | Dim1D_2D_3D | DimCube | SFloat          }, // RGBA64Float

        /* --- BGRA color formats --- */
        //   bits  w  h  c  format                   dataType
        {  32, 1, 1, 4, ColorFormat::BGRA,         DataType::UInt8,     GenMips | Dim1D_2D_3D | DimCube | UNorm                    }, // BGRA8UNorm
        {  32, 1, 1, 4, ColorFormat::BGRA,         DataType::UInt8,     GenMips | Dim1D_2D_3D | DimCube | UNorm | sRGB             }, // BGRA8UNorm_sRGB
        {  32, 1, 1, 4, ColorFormat::BGRA,         DataType::Int8,      GenMips | Dim1D_2D_3D | DimCube | SNorm                    }, // BGRA8SNorm
        {  32, 1, 1, 4, ColorFormat::BGRA,         DataType::UInt8,     GenMips | Dim1D_2D_3D | DimCube | UInt                     }, // BGRA8UInt
        {  32, 1, 1, 4, ColorFormat::BGRA,         DataType::Int8,      GenMips | Dim1D_2D_3D | DimCube | SInt                     }, // BGRA8SInt

        /* --- Packed formats --- */
        //   bits  w  h  c  format                   dataType
        {  32, 1, 1, 4, ColorFormat::RGBA,         DataType::Undefined, GenMips | Dim1D_2D_3D | DimCube | UNorm | Packed           }, // RGB10A2UNorm
        {  32, 1, 1, 4, ColorFormat::RGBA,         DataType::Undefined, GenMips | Dim1D_2D_3D | DimCube | UInt | Packed            }, // RGB10A2UInt
        {  32, 1, 1, 3, ColorFormat::RGB,          DataType::Undefined, GenMips | Dim1D_2D_3D | DimCube | UFloat | Packed          }, // RG11B10Float
        {  32, 1, 1, 3, ColorFormat::RGB,          DataType::Undefined, Mips | Dim1D_2D_3D | DimCube | UFloat | Packed             }, // RGB9E5Float

        /* --- Depth-stencil formats --- */
        //   bits  w  h  c  format                   dataType
        {  16, 1, 1, 1, ColorFormat::Depth,        DataType::UInt16,    Mips | RTV | Dim1D_2D | DimCube | UNorm | Depth            }, // D16UNorm
        {  32, 1, 1, 2, ColorFormat::DepthStencil, DataType::UInt16,    Mips | RTV | Dim1D_2D | DimCube | UNorm | Depth | Stencil  }, // D24UNormS8UInt
        {  32, 1, 1, 1, ColorFormat::Depth,        DataType::Float32,   Mips | RTV | Dim1D_2D | DimCube | SFloat | Depth           }, // D32Float
        {  64, 1, 1, 2, ColorFormat::DepthStencil, DataType::Float32,   Mips | RTV | Dim1D_2D | DimCube | SFloat | Depth | Stencil }, // D32FloatS8X24UInt
        {   8, 1, 1, 1, ColorFormat::Stencil,      DataType::UInt8,     Mips | RTV | Dim1D_2D | DimCube | UInt   | Stencil         }, // S8UInt

        /* --- Block compression (BC) formats --- */
        //   bits  w  h  c  format                   dataType
        {  64, 4, 4, 4, ColorFormat::BC1,          DataType::UInt8,     Mips | Dim2D_3D | DimCube | Compr | UNorm                  }, // BC1UNorm
        {  64, 4, 4, 4, ColorFormat::BC1,          DataType::UInt8,     Mips | Dim2D_3D | DimCube | Compr | UNorm | sRGB           }, // BC1UNorm_sRGB
        { 128, 4, 4, 4, ColorFormat::BC2,          DataType::UInt8,     Mips | Dim2D_3D | DimCube | Compr | UNorm                  }, // BC2UNorm
        { 128, 4, 4, 4, ColorFormat::BC2,          DataType::UInt8,     Mips | Dim2D_3D | DimCube | Compr | UNorm | sRGB           }, // BC2UNorm_sRGB
        { 128, 4, 4, 4, ColorFormat::BC3,          DataType::UInt8,     Mips | Dim2D_3D | DimCube | Compr | UNorm                  }, // BC3UNorm
        { 128, 4, 4, 4, ColorFormat::BC3,          DataType::UInt8,     Mips | Dim2D_3D | DimCube | Compr | UNorm | sRGB           }, // BC3UNorm_sRGB
        {  64, 4, 4, 1, ColorFormat::BC4,          DataType::UInt8,     Mips | Dim2D_3D | DimCube | Compr | UNorm                  }, // BC4UNorm
        {  64, 4, 4, 1, ColorFormat::BC4,          DataType::Int8,      Mips | Dim2D_3D | DimCube | Compr | SNorm                  }, // BC4SNorm
        { 128, 4, 4, 2, ColorFormat::BC5,          DataType::UInt8,     Mips | Dim2D_3D | DimCube | Compr | UNorm                  }, // BC5UNorm
        { 128, 4, 4, 2, ColorFormat::BC5,          DataType::Int8,      Mips | Dim2D_3D | DimCube | Compr | SNorm                  }, // BC5SNorm
    };

    const FormatAttributes& GetFormatAttribs(const Format& format)
    {
        auto idx = static_cast<size_t>(format);
        if (idx < sizeof(g_formatAttribs) / sizeof(g_formatAttribs[0]))
            return g_formatAttribs[idx];
        else
            return g_formatAttribs[0];
    }

    bool IsCompressedFormat(const Format& format)
    {
        return ((GetFormatAttribs(format).flags & FormatFlags::IsCompressed) != 0);
    }

    bool IsDepthStencilFormat(const Format& format)
    {
        const auto& formatAttribs = GetFormatAttribs(format);
        return ((formatAttribs.flags & (FormatFlags::HasDepth | FormatFlags::HasStencil)) != 0);
    }

    bool IsDepthFormat(const Format& format)
    {
        return ((GetFormatAttribs(format).flags & (FormatFlags::HasDepth)) != 0);
    }

    bool IsStencilFormat(const Format& format)
    {
        return ((GetFormatAttribs(format).flags & FormatFlags::HasStencil) != 0);
    }

    bool IsNormalizedFormat(const Format& format)
    {
        return ((GetFormatAttribs(format).flags & FormatFlags::IsNormalized) != 0);
    }

    bool IsIntegralFormat(const Format& format)
    {
        if (format >= Format::R8UNorm &&
            format <= Format::BGRA8SInt)
            return !IsFloatFormat(format);
        else
            return false;
    }

    bool IsFloatFormat(const Format& format)
    {
        switch (format)
        {
        case Format::R16Float:
        case Format::R64Float:
        case Format::R32Float:
        case Format::RG16Float:
        case Format::RG32Float:
        case Format::RG64Float:
        case Format::RGB16Float:
        case Format::RGB32Float:
        case Format::RGB64Float:
        case Format::RGBA16Float:
        case Format::RGBA32Float:
        case Format::RGBA64Float:
            return true;
        default:
            return false;
        }
    }

    int DataTypeSize(const DataType& dataType)
    {
        switch (dataType)
        {
        case DataType::Undefined:   break;
        case DataType::Int8:        return 1;
        case DataType::UInt8:       return 1;
        case DataType::Int16:       return 2;
        case DataType::UInt16:      return 2;
        case DataType::Int32:       return 4;
        case DataType::UInt32:      return 4;
        case DataType::Float16:     return 2;
        case DataType::Float32:     return 4;
        case DataType::Float64:     return 8;
        }
        return 0;
    }

    bool IsIntDataType(const DataType& dataType)
    {
        return (dataType == DataType::Int8 || 
                dataType == DataType::Int16 || 
                dataType == DataType::Int32);
    }

    bool IsUIntDataType(const DataType& dataType)
    {
        return (dataType == DataType::UInt8 || 
                dataType == DataType::UInt16 || 
                dataType == DataType::UInt32);
    }

    bool IsFloatDataType(const DataType& dataType)
    {
        return (dataType >= DataType::Float16 && 
                dataType <= DataType::Float64);
    }

    int ColorFormatSize(const ColorFormat& colorType)
    {
        switch (colorType)
        {
        case ColorFormat::Alpha:            return 1;
        case ColorFormat::R:                return 1;
        case ColorFormat::RG:               return 2;
        case ColorFormat::RGB:              return 3;
        case ColorFormat::BGR:              return 3;
        case ColorFormat::RGBA:             return 4;
        case ColorFormat::BGRA:             return 4;
        case ColorFormat::ARGB:             return 4;
        case ColorFormat::ABGR:             return 4;
        case ColorFormat::Depth:            return 1;
        case ColorFormat::DepthStencil:     return 2;
        case ColorFormat::BC1:              return 0; // no conversion supported yet
        case ColorFormat::BC2:              return 0; // no conversion supported yet
        case ColorFormat::BC3:              return 0; // no conversion supported yet
        case ColorFormat::BC4:              return 0; // no conversion supported yet
        case ColorFormat::BC5:              return 0; // no conversion supported yet
        }
        return 0;
    }

    bool IsCompressedFormat(const ColorFormat& colorType)
    {
        return (colorType >= ColorFormat::BC1 && 
                colorType <= ColorFormat::BC5);
    }

    bool IsDepthStencilFormat(const ColorFormat& colorType)
    {
        return (colorType == ColorFormat::Depth || 
                colorType == ColorFormat::DepthStencil);
    }
}