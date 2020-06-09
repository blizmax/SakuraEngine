/*
 * @CopyRight: MIT License
 * Copyright (c) 2020 SaeruHikari
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THESOFTWARE.
 * 
 * 
 * @Description: 
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-06-08 23:26:09
 * @LastEditTime: 2020-06-09 13:38:17
 */ 
#include "../Include/ShaderTranslator/ShaderTranslator.h"
using namespace Sakura::Graphics;
#include <codecvt>
#include <spirv_cross/spirv_glsl.hpp>

bool Sakura::Graphics::HLSLShaderCompiler::Compile(
    const ShaderCompileDesc& compileDesc,
    const Sakura::Graphics::ShaderILBC target,
    ShaderCompileQuery* query)
{
    if(query == nullptr)
        if(compileDesc.shaderFileName.empty() || compileDesc.binaryPath.empty())
            return false;
    // 
    // Create compiler and utils.
    //
    DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&pUtils));
    DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&pCompiler));
    //
    // Create default include handler. (You can create your own...)
    //
    pUtils->CreateDefaultIncludeHandler(&pIncludeHandler);
    Sakura::swstring stage;
    switch(compileDesc.shaderStage)
    {
        case ShaderStageFlags::VertexStage:
            stage = L"vs_6_6";break;
        case ShaderStageFlags::HullStage:
            stage = L"hs_6_6";break;
        case ShaderStageFlags::DomainStage:
            stage = L"ds_6_6";break;
        case ShaderStageFlags::GeometryStage:
            stage = L"gs_6_6";break;
        case ShaderStageFlags::PixelStage:
            stage = L"ps_6_6";break;
        case ShaderStageFlags::ComputeStage:
            stage = L"cs_6_6";break;
        case ShaderStageFlags::RayGeneration:
        case ShaderStageFlags::RayAnyHit:
        case ShaderStageFlags::RayClosestHit:
        case ShaderStageFlags::RayMiss:
            stage = L"lib_6_6";break;
        case ShaderStageFlags::AmplificationStage:
            stage = L"as_6_6";break;
        case ShaderStageFlags::MeshStage:
            stage = L"ms_6_6";break;
        default:
            return false;
    }
    Sakura::svector<LPCWSTR> pszArgs =
    {
        // shader file name
        compileDesc.shaderFileName.c_str(),            // Optional shader source file name for error reporting and for PIX shader source view.  
        // entry point
        L"-E", compileDesc.entryPoint.c_str(),              
        // shader stage
        L"-T", stage.c_str(),            
        compileDesc.bEnableDebugInformation ? L"-Zi" : L"", // Enable debug information.
        //L"-D", L"MYDEFINE=1",        // A single define.
        L"-Fo", compileDesc.binaryPath.c_str(),     // Optional. Stored in the pdb. 
        // PDB file generate
        compileDesc.pdbPath.empty() ? L"" : L"-Fd",
        compileDesc.pdbPath.empty() ? L"" : compileDesc.pdbPath.c_str(),     // The file name of the pdb. This must either be supplied or the autogenerated file name must be used.
        //L"-Qstrip_reflect",          // Strip reflection into a separate blob.
        L"-fspv-reflect",          // Strip reflection into a separate blob.
        (target == ShaderILBC::DXBC || target == ShaderILBC::DXIL) 
            ?  L"" : L"-spirv",
    };
    for(auto&& arg : compileDesc.compilerArgs)
    {
        pszArgs.push_back(arg.c_str());
    }

    //
    // Open source file.  
    //
    CComPtr<IDxcBlobEncoding> pSource = nullptr;
    pUtils->LoadFile(compileDesc.shaderFileName.c_str(), nullptr, &pSource);
    DxcBuffer Source;
    Source.Ptr = pSource->GetBufferPointer();
    Source.Size = pSource->GetBufferSize();
    Source.Encoding = DXC_CP_ACP; // Assume BOM says UTF8 or UTF16 or this is ANSI text.


    //
    // Compile it with specified arguments.
    //
    CComPtr<IDxcResult> pResults;
    pCompiler->Compile(
        &Source,                // Source buffer.
        pszArgs.data(),                // Array of pointers to arguments.
        pszArgs.size(),      // Number of arguments.
        pIncludeHandler,        // User-provided interface to handle #include directives (optional).
        IID_PPV_ARGS(&pResults) // Compiler output status, buffer, and errors.
    );

    //
    // Print errors if present.
    //
    CComPtr<IDxcBlobUtf8> pErrors = nullptr;
    pResults->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&pErrors), nullptr);
    // Note that d3dcompiler would return null if no errors or warnings are present.  
    // IDxcCompiler3::Compile will always return an error buffer, but its length will be zero if there are no warnings or errors.
    if (pErrors != nullptr && pErrors->GetStringLength() != 0)
        wprintf(L"Warnings and Errors:\n%S\n", pErrors->GetStringPointer());

    //
    // Quit if the compilation failed.
    //
    HRESULT hrStatus;
    pResults->GetStatus(&hrStatus);
    if (FAILED(hrStatus))
    {
        wprintf(L"Compilation Failed\n");
        return false;
    }

    //
    // Save shader binary.
    //
    CComPtr<IDxcBlob> pShader = nullptr;
    CComPtr<IDxcBlobUtf16> pShaderName = nullptr;
    pResults->GetOutput(
        DXC_OUT_OBJECT, IID_PPV_ARGS(&pShader), &pShaderName);
    if (!compileDesc.binaryPath.empty() && pShader != nullptr)
    {
        if(query)
        {
            query->compiledBlob = pShader;
            query->shaderName = pShaderName;
        }
        FILE* fp = NULL;
        std::wstring name = pShaderName->GetStringPointer();
        std::string utf8N;
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        utf8N = conv.to_bytes(name);
        fp = fopen(utf8N.c_str(), "wb");
        fwrite(pShader->GetBufferPointer(), pShader->GetBufferSize(), 1, fp);
        fclose(fp);
    }

    //
    // Save pdb.
    //
    CComPtr<IDxcBlob> pPDB = nullptr;
    CComPtr<IDxcBlobUtf16> pPDBName = nullptr;
    pResults->GetOutput(DXC_OUT_PDB, IID_PPV_ARGS(&pPDB), &pPDBName);
    if(!compileDesc.pdbPath.empty() && pPDB != nullptr)
    {
        FILE* fp = NULL;
        std::wstring name = pPDBName->GetStringPointer();
        std::string utf8N;
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        utf8N = conv.to_bytes(name);
        fp = fopen(utf8N.c_str(), "wb");
        fwrite(pPDB->GetBufferPointer(), pPDB->GetBufferSize(), 1, fp);
        fclose(fp);
    }

    //
    // Print hash.
    //
    CComPtr<IDxcBlob> pHash = nullptr;
    pResults->GetOutput(DXC_OUT_SHADER_HASH, IID_PPV_ARGS(&pHash), nullptr);
    if (pHash != nullptr)
    {
        if(query)
        {
            query->shaderHash = pHash;
        }
        wprintf(L"Hash: ");
        DxcShaderHash* pHashBuf = (DxcShaderHash*)pHash->GetBufferPointer();
        for (int i = 0; i < _countof(pHashBuf->HashDigest); i++)
            wprintf(L"%x", pHashBuf->HashDigest[i]);
        wprintf(L"\n");
    }


    //
    // Get separate reflection.
    //
    //CComPtr<IDxcBlob> pReflectionData;
    //pResults->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&pReflectionData), nullptr);
    /*if (pReflectionData != nullptr)
    {
        // Optionally, save reflection blob for later here.

        // Create reflection interface.
        DxcBuffer ReflectionData;
        ReflectionData.Encoding = DXC_CP_ACP;
        ReflectionData.Ptr = pReflectionData->GetBufferPointer();
        ReflectionData.Size = pReflectionData->GetBufferSize();

        CComPtr<ID3D12ShaderReflection> pReflection;
        pUtils->CreateReflection(&ReflectionData, IID_PPV_ARGS(&pReflection));

        // Use reflection interface here.
    }*/
    return true;
}