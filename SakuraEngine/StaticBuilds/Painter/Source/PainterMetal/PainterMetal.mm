#import "PainterMetal.h"
#import "RenderPass.h"
#import "ShaderMetal.h"
#import "Fence.h"
#import "mtlpp/library.hpp"
#import "BufferMetal.h"
#import "SwapChainMetal.h"
#import <MetalKit/MetalKit.h>

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
            PainterMetal::error("Create Metal Shader Function Failed!");
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




GPUBuffer* PainterMetal::CreateBuffer( 
    const GPUBuffer::BufferUsage usage, 
    const GPUResource::ResourceOptions options, 
    std::uint32_t length, const void* pointer)
{
    assert(pointer != nullptr);
    auto flag = 
        (options == GPUResource::ResourceOptions::Default) ? 
        mtlpp::ResourceOptions::StorageModePrivate :
        (options == GPUResource::ResourceOptions::Query) ?
        mtlpp::ResourceOptions::StorageModeManaged :
        mtlpp::ResourceOptions::StorageModeShared;
    return new BufferMetal(
            device.NewBuffer(pointer, length,
            mtlpp::ResourceOptions::HazardTrackingModeUntracked | flag),
        usage);
}


//---------------SwapChain Create and Initialization---------------
void SwapChainMetal::initWithCAMetalLayer(Painter& painter, void* layer)
{
    PainterMetal::debug_info("Init a swap chain with CAMetalLayer!");

}
