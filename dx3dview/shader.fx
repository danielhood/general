//--------------------------------------------------------------------------------------
// File: shader.fx
//
//--------------------------------------------------------------------------------------

// Global Vars
float3 LightDir;                  // Light's direction in world space

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D txDiffuse;
SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

cbuffer cbNeverChanges
{
    matrix View;
};

cbuffer cbChangeOnResize
{
    matrix Projection;
};

cbuffer cbChangesEveryFrame
{
    matrix World;
};


// Shader Strucutres
struct VS_INPUT
{
    float4 Pos : POSITION;
	float4 N: NORMAL;
//    float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float4 Diffuse    : COLOR0;     // vertex diffuse color (note that COLOR0 is clamped from 0..1)
//    float2 Tex : TEXCOORD0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );

	float3 vNormalWorldSpace;
	// Transform the normal from object space to world space    
    vNormalWorldSpace = normalize( mul( input.N, (float3x3)World ) );
	//vNormalWorldSpace = normalize(mul (mul(mul( input.N, (float3x3)World ), View), Projection));

	float3 cLit = {0.2f, 0.2f, 0.8f};
	float3 cDark = {0.075f, 0.075f, 0.4f};
	output.Diffuse.rgb = cLit * max( 0,dot( vNormalWorldSpace, LightDir ) ) + cDark;
	//output.Diffuse.rgb = max( 0,dot( vNormalWorldSpace, LightDir ) );
	//output.Diffuse.rgb = min( 1.0f, output.Diffuse.rgb+0.3); 
	
	//output.Diffuse.rgb = cDark * input.N;
	//output.Diffuse.rgb = input.N.x;
    output.Diffuse.a = 1.0f; 
	
    //output.Tex = input.Tex;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
    float4 RGBColor : SV_TARGET;  // Pixel color    
};


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
PS_OUTPUT PS( PS_INPUT input) 
{
	PS_OUTPUT output;

    output.RGBColor = input.Diffuse;
	return output;
}


//--------------------------------------------------------------------------------------
technique10 Render
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0_level_9_1, VS() ) );

        SetGeometryShader( NULL );

        SetPixelShader( CompileShader( ps_4_0_level_9_1, PS() ) );
    }
}

