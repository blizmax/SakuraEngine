struct VertexOut
{
    float4 position : SV_Position;
};

// /Users/huangzheng/Coding/SakuraEngine/Debug-build/Engine/tools/DirectXShaderCompiler/dxc-3.7 -spirv -E fragFunc -T ps_6_6 -Fo /Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/TrianglePS.spv /Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/TrianglePS.hlsl

float4 fragFunc(VertexOut pin) : SV_TARGET
{
    return float4(1.f, 1.f, 1.f, 1.f);
}
/*
struct fragFunc_out
{
    float4 out_var_SV_TARGET [[color(0)]];
};

fragment fragFunc_out fragFunc()
{
    fragFunc_out out = {};
    out.out_var_SV_TARGET = float4(1.0);
    return out;
}
*/