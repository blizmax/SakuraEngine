#import "PainterMetal.h"
#import "RenderPass.h"
#import "ShaderMetal.h"
#import "Fence.h"
#import "mtlpp/library.hpp"

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

Fence* PainterMetal::CreateFence()
{
    return nullptr;
}

RenderPass* PainterMetal::CreateRenderPass(const RenderPassDesc& desc)
{
    return nullptr;
}


ShaderMetal::ShaderMetal(mtlpp::Library lib)
    :library(lib)
{
    if(library.GetPtr() == nullptr)
        PainterMetal::error("Failed to create ShaderLibrary Metal!");
}

const void* ShaderMetal::NewFunctionHandle(
    const eastl::string& entryName)
{
    if(shaderFunctions.find(entryName) == shaderFunctions.end())
    {
        mtlpp::Function func = library.NewFunction(entryName.c_str());
        if(func.GetPtr() == nullptr)
        {
            PainterMetal::debug_error("Create Metal Shader Function Failed!");
        }
        shaderFunctions[entryName] = func;
    }
    if(shaderFunctions[entryName].GetPtr() == nullptr)
        PainterMetal::error("Failed to create ShaderFunction Metal!");
    return shaderFunctions[entryName].GetPtr();
}

Shader* PainterMetal::CreateShader(
    const char* data, std::size_t dataSize, const Shader::MacroTable& macroTable)
{
    mtlpp::Library library 
        = device.NewLibrary(data, mtlpp::CompileOptions(), nullptr);
    return new ShaderMetal(library);
}