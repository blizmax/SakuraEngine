#pragma once
#include "SakuraEngine/StaticBuilds/Painter/Include/SakuraPainter.h"
#include <iostream>

using namespace Sakura::Graphics;

struct NullExtension : public Extension
{
    NullExtension(int index)
    {
        
    }
    static bool EnableIf(Painter* painter)
    {
        return true;
    }
    void NullTest()
    {
        std::cout << name << std::endl;
    }
    inline static constexpr const char* name = "NullExtension";
};

const char shadersSrc[] = R"""(
    #include <metal_stdlib>
    using namespace metal;

    vertex float4 vertFunc(
        const device packed_float3* vertexArray [[buffer(0)]],
        unsigned int vID[[vertex_id]])
    {
        return float4(vertexArray[vID], 1.0);
    }

    fragment half4 fragFunc()
    {
        return half4(1.0, 0.0, 0.0, 1.0);
    }
)""";

class PainterMetalApp
{
public:
    void run()
    {
        Painter* painter = Painter::Create<Metal::PainterMetal>(true);
        auto ext = painter->EnableExtension<NullExtension>(5);
        if(ext)
            ext->NullTest();
        auto shader = painter->CreateShader(shadersSrc, strlen(shadersSrc));
        auto vertFunction 
            = ShaderFunction(ShaderStageFlags::VertexStage, shader, "vertFunc");
        auto pixelFunction 
            = ShaderFunction(ShaderStageFlags::PixelStage, shader, "fragFunc");
        return;
    }
};