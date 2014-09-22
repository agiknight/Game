
// -------------------------------------------------------------
// ��������
// -------------------------------------------------------------
float4x4 mWorld;
float4x4 mVP;		// ���ÿ��� �������������� ��ǥ��ȯ
float4x4 mWIT;
float3 vLightDir = {0, -1, 0};
float3 vEyePos;
float4 globalAmbient = {0.2f, 0.2f, 0.2f, 1.0f};

// ���� ���.
float4 I_a = {0.3f, 0.3f, 0.3f, 0.0f}; // ambient
float4 I_d = {1.f, 1.f, 1.f, 0.0f}; // diffuse
float4 I_s = {1.f, 1.f, 1.f, 0.0f}; // diffuse

// �ݻ���
float4 K_a = {1.0f, 1.0f, 1.0f, 1.0f}; // ambient 
float4 K_d = {1.0f, 1.0f, 1.0f, 1.0f}; // diffuse

// �ȷ�Ʈ
float4x3 mPalette[ 64];


// ------------------------------------------------------------
// �ؽ�ó
// ------------------------------------------------------------
texture colorMapTexture;
sampler colorMap = sampler_state
{
    Texture = <colorMapTexture>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;
};


// ------------------------------------------------------------
// ��ָ�
// ------------------------------------------------------------
texture normalMapTexture;
sampler2D normalMap = sampler_state
{
    Texture = <normalMapTexture>;
    MagFilter = Linear;
    MinFilter = Anisotropic;
    MipFilter = Linear;
    MaxAnisotropy = 16;
};


struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Diffuse : COLOR0;
	float2 Tex : TEXCOORD0;
	float3 Eye : TEXCOORD1;
	float3 N : TEXCOORD2;
};


// �׸��� �� ��¿� ����ü.
struct VS_SHADOW_OUTPUT
{
	float4 Pos : POSITION;
	float4 Diffuse : COLOR0;
};


struct VS_BUMP_OUTPUT
{
    float4 Pos	 : POSITION;
	float2 Tex : TEXCOORD0;
	float3 HalfVector : TEXCOORD1;
	float3 LightDir : TEXCOORD2;
};



// -------------------------------------------------------------
// 0�н�:�������̴�
// -------------------------------------------------------------
VS_OUTPUT VS_pass0(
	float4 Pos : POSITION,          // ������
	float3 Normal : NORMAL,		// ��������
	float2 Tex : TEXCOORD0,		// �ؽ��� ��ǥ
	float4 Weights : TEXCOORD1,	// ���ؽ� ����ġ
	float4 BoneIndices : TEXCOORD2 // �� �ε��� (4�� ����)
)
{
	VS_OUTPUT Out = (VS_OUTPUT)0; // ��µ�����
    
	// ��ǥ��ȯ
	float4x4 mWVP = mul(mWorld, mVP);

	float3 p = {0,0,0};
	float3 n = {0,0,0};

	p += mul(Pos, mPalette[ BoneIndices.x]).xyz * Weights.x;
	p += mul(Pos, mPalette[ BoneIndices.y]).xyz * Weights.y;
	p += mul(Pos, mPalette[ BoneIndices.z]).xyz * Weights.z;
	p += mul(Pos, mPalette[ BoneIndices.w]).xyz * Weights.w;

	n += mul(float4(Normal,0), mPalette[ BoneIndices.x]).xyz * Weights.x;
	n += mul(float4(Normal,0), mPalette[ BoneIndices.y]).xyz * Weights.y;
	n += mul(float4(Normal,0), mPalette[ BoneIndices.z]).xyz * Weights.z;
	n += mul(float4(Normal,0), mPalette[ BoneIndices.w]).xyz * Weights.w;

	Out.Pos = mul( float4(p,1), mWVP );
	n = normalize(n);

	// ���� ���� ���.
	float3 N = normalize( mul(n, (float3x3)mWIT) ); // ���� ��ǥ�迡���� ����.
	
	Out.N = N;
	Out.Eye = vEyePos - Pos.xyz;
	Out.Tex = Tex;
    
    return Out;
}


// -------------------------------------------------------------
// 0�н�:�ȼ����̴�
// -------------------------------------------------------------
float4 PS_pass0(VS_OUTPUT In) : COLOR
{
	float4 Out;
	Out = tex2D(colorMap, In.Tex);
    return Out;
}



// -------------------------------------------------------------
// 1�н�:�������̴�, �׸��� �� ���.
// -------------------------------------------------------------
VS_SHADOW_OUTPUT VS_pass1(
	float4 Pos : POSITION,          // ������
	float3 Normal : NORMAL,		// ��������
	float2 Tex : TEXCOORD0,		// �ؽ��� ��ǥ
	float4 Weights : TEXCOORD1,	// ���ؽ� ����ġ
	float4 BoneIndices : TEXCOORD2 // �� �ε��� (4�� ����)
)
{
	VS_SHADOW_OUTPUT Out = (VS_SHADOW_OUTPUT)0; // ��µ�����
    
	// ��ǥ��ȯ
	float4x4 mWVP = mul(mWorld, mVP);

	float3 p = {0,0,0};

	p += mul(Pos, mPalette[ BoneIndices.x]) * Weights.x;
	p += mul(Pos, mPalette[ BoneIndices.y]) * Weights.y;
	p += mul(Pos, mPalette[ BoneIndices.z]) * Weights.z;
	p += mul(Pos, mPalette[ BoneIndices.w]) * Weights.w;

	Out.Pos = mul( float4(p,1), mWVP );
	Out.Diffuse = float4(1,1,1,1);
    
    return Out;
}



// -------------------------------------------------------------
// 4�н�:�������̴�
// D3D9NormalMapping �ҽ��� ���� ��.
// http://www.dhpoware.com/demos/d3d9NormalMapping.html
// -------------------------------------------------------------
VS_BUMP_OUTPUT VS_pass4(
	float4 Pos : POSITION,          // ������
	float3 Normal : NORMAL,		// ��������
	float2 Tex : TEXCOORD0,		// �ؽ��� ��ǥ
	float4 Weights : TEXCOORD1,	// ���ؽ� ����ġ
	float4 BoneIndices : TEXCOORD2, // �� �ε��� (4�� ����)
	float3 tangent : TANGENT,		// tangent ����
	float3 binormal : BINORMAL 	// binormal ����
)
{
	VS_BUMP_OUTPUT Out = (VS_BUMP_OUTPUT)0; // ��µ�����
    
	float3 p = {0,0,0};
	float3 n = {0,0,0};

	p += mul(Pos, mPalette[ BoneIndices.x]).xyz * Weights.x;
	p += mul(Pos, mPalette[ BoneIndices.y]).xyz * Weights.y;
	p += mul(Pos, mPalette[ BoneIndices.z]).xyz * Weights.z;
	p += mul(Pos, mPalette[ BoneIndices.w]).xyz * Weights.w;

	n += mul(float4(Normal,0), mPalette[ BoneIndices.x]).xyz * Weights.x;
	n += mul(float4(Normal,0), mPalette[ BoneIndices.y]).xyz * Weights.y;
	n += mul(float4(Normal,0), mPalette[ BoneIndices.z]).xyz * Weights.z;
	n += mul(float4(Normal,0), mPalette[ BoneIndices.w]).xyz * Weights.w;

	//Out.Pos = mul( float4(p,1), mWVP );
	//n = normalize(n);

	float3 worldPos = mul(float4(p,1), mWorld).xyz;
	float3 lightDir = -vLightDir;
	float3 viewDir = vEyePos - worldPos;
	float3 halfVector = normalize(normalize(lightDir) + normalize(viewDir));

			  n = normalize( mul(n, (float3x3)mWIT) ); // ���� ��ǥ�迡���� ����.
	float3 t = normalize( mul(tangent, (float3x3)mWIT) ); // ���� ��ǥ�迡���� ź��Ʈ
	float3 b = normalize( mul(binormal, (float3x3)mWIT) ); // ���� ��ǥ�迡���� ���̳��
	float3x3 tbnMatrix = float3x3(t.x, b.x, n.x,
	                              t.y, b.y, n.y,
	                              t.z, b.z, n.z);

	Out.Pos = mul( float4(worldPos,1), mVP );
	Out.Tex = Tex;
	Out.HalfVector = mul(halfVector, tbnMatrix);
	Out.LightDir = mul(lightDir, tbnMatrix);    

    return Out;
}


// -------------------------------------------------------------
// 4�н�:�ȼ����̴�
// -------------------------------------------------------------
float4 PS_pass4(VS_BUMP_OUTPUT In) : COLOR
{
	// ��Ÿ2 ��ָ��� rgba ������ ����Ȱ� �ƴ϶�. bgxr ���·� ����Ǿ� �ִ�.
	// �׷��� ��ְ��� ����� ���������� agr ���� �����;� rgb�� xyz ������� 
	// �������� �ȴ�.
	// http://blog.naver.com/scahp/130109083917
	// http://forum.xentax.com/viewtopic.php?f=16&t=6119&start=15
	float4 nt = tex2D(normalMap, In.Tex);
	float3 n = normalize(float3(nt.a, nt.g, nt.r)  * 2.0f - 1.0f);

	// �Ϲ� ��ָʿ�. ���� ������ ����.
   //float3 n = normalize(tex2D(normalMap, In.Tex).rgb * 2.0f - 1.0f);

    float3 h = normalize(In.HalfVector);
    float3 l = normalize(In.LightDir);

	float shininess = 90;
    float nDotL = saturate(dot(n, l));
    float nDotH = saturate(dot(n, h));
    float power = (nDotL == 0.0f) ? 0.0f : pow(nDotH, shininess);

    float4 color = (globalAmbient + I_a) 
						+ (I_d * nDotL) 
						+ (I_s * power);

	return  color * tex2D(colorMap, In.Tex);
}


	
// -------------------------------------------------------------
// ��ũ��
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        // ���̴�
        VertexShader = compile vs_3_0 VS_pass0();
		PixelShader  = compile ps_3_0 PS_pass0();
    }

    pass P1
    {
        // �׸��� �� ���̴�
        VertexShader = compile vs_3_0 VS_pass1();
    }

    pass P2
    {
	// �ƹ��͵� ����.
    }

    pass P3
    {
	// �ƹ��͵� ����.
    }

    pass P4
    {
		// ��Ű�� �ִϸ��̼� + ���� ��.
        VertexShader = compile vs_3_0 VS_pass4();
		PixelShader  = compile ps_3_0 PS_pass4();
    }

}

