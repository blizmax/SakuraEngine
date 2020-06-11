struct VertexIn
{
    float3 inPos : SV_Position;
};

struct VertexOut
{
    float4 position : SV_Position;
};

VertexOut vertFunc(VertexIn vin)
{
    VertexOut vout;
    vout.position = float4(vin.inPos.xyz, 1.f);
    return vout;
}

/* MSL Generated
    #include <metal_stdlib>
    #include <simd/simd.h>

    using namespace metal;

    struct vertFunc_out
    {
        float4 gl_Position [[position]];
    };

    struct vertFunc_in
    {
        float3 in_var_SV_Position [[attribute(0)]];
    };

    vertex vertFunc_out vertFunc(vertFunc_in in [[stage_in]])
    {
        vertFunc_out out = {};
        out.gl_Position = float4(in.in_var_SV_Position, 1.0);
        return out;
    }
*/

// /Users/huangzheng/Coding/SakuraEngine/Debug-build/Engine/tools/DirectXShaderCompiler/dxc-3.7 -spirv -E vertFunc -T vs_6_6 /Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/Triangle.hlsl
// /Users/huangzheng/Coding/SakuraEngine/Debug-build/Engine/tools/DirectXShaderCompiler/dxc-3.7 -spirv -E vertFunc -T vs_6_6 -Fo /Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/Triangle.spv /Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/Triangle.hlsl
