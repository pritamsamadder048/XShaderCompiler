/*
 * XscTest1.c
 * 
 * This file is part of the XShaderCompiler project (Copyright (c) 2014-2017 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include <XscC/XscC.h>
#include <stdio.h>


#define PRINT_FUNC                              \
    puts("");                                   \
    puts("");                                   \
    printf("~~~~~ %s ~~~~~\n", __FUNCTION__);   \
    puts("")

void TestGLSLExtensions()
{
    PRINT_FUNC;

    char extension[256];
    int version;

    // Get first extension
    void* iterator = XscGetGLSLExtensionEnumeration(NULL, extension, 256, &version);

    while (iterator != NULL)
    {
        // Print extension name and version
        printf("%s ( %d )\n", extension, version);
    
        // Get next extension
        iterator = XscGetGLSLExtensionEnumeration(iterator, extension, 256, &version);
    }
}

void TestShaderTarget()
{
    PRINT_FUNC;

    char target[64];

    XscShaderTargetToString(XscETargetVertexShader, target, 64);
    puts(target);

    XscShaderTargetToString(XscETargetTessellationControlShader, target, 64);
    puts(target);
}

void TestCompile()
{
    PRINT_FUNC;

    // Initialize structures
    struct XscShaderInput in;
    struct XscShaderOutput out;
    XscInitialize(&in, &out);

    const char* outputCode = NULL;

    // Specify shader code
    in.filename     = "test.hlsl";
    in.entryPoint   = "VS";
    in.shaderTarget = XscETargetVertexShader;
    in.sourceCode   =
    (
        "cbuffer Matrices {\n"
        "    float4x4 wvpMatrix;\n"
        "};\n"
        "float4 VS(float3 pos : POSITION) : SV_Position {\n"
        "    return mul(wvpMatrix, float4(pos, 1));\n"
        "}\n"
    );
    
    out.filename    = "test.VS.vert";
    out.sourceCode  = &outputCode;

    // Compile shader
    puts(in.sourceCode);

    if (XscCompileShader(&in, &out, XSC_DEFAULT_LOG))
    {
        puts("*** COMPILATION SUCCESSFUL ***\n");
        if (outputCode != NULL)
            puts(outputCode);
    }
    else
        puts("*** COMPILATION FAILED ***");
}

int main()
{
    puts("XscTest1");

    TestGLSLExtensions();
    TestShaderTarget();
    TestCompile();

    return 0;
}



// ================================================================================