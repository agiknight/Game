
// -------------------------------------------------------------
// ��������
// -------------------------------------------------------------
float4x4 mWorld;
float4x4 mVP;		// ���ÿ��� �������������� ��ǥ��ȯ
float4x4 mWIT;
float3 vLightDir = {0, -1, 0};
float3 vEyePos;

// ���� ���.
float4 I_a = {0.3f, 0.3f, 0.3f, 0.0f}; // ambient
float4 I_d = {1.f, 1.f, 1.f, 0.0f}; // diffuse
float4 I_s = {1.f, 1.f, 1.f, 0.0f}; // diffuse

// �ݻ���
float4 K_a = {1.0f, 1.0f, 1.0f, 1.0f}; // ambient 
float4 K_d = {1.0f, 1.0f, 1.0f, 1.0f}; // diffuse

// �ȷ�Ʈ
float4x4 mPalette[ 64];




// ------------------------------------------------------------
// �ؽ�ó
// ------------------------------------------------------------
texture Tex;
sampler Samp = sampler_state
{
    Texture = <Tex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;
};


// -------------------------------------------------------------
// �������̴����� �ȼ����̴��� �ѱ�� ������
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Diffuse : COLOR0;
	float2 Tex : TEXCOORD0;
};


// -------------------------------------------------------------
// 1�н�:�������̴�
// -------------------------------------------------------------
VS_OUTPUT VS_pass0(
	float4 Pos : POSITION,          // ������
	float3 Normal : NORMAL,		// ��������
	float4 BonIndices : COLOR0, // �� �ε��� (4�� ����)
	float2 Tex : TEXCOORD0,
	float4 Weights : BLENDWEIGHT	// ���ؽ� ����ġ
)
{
	VS_OUTPUT Out = (VS_OUTPUT)0; // ��µ�����
    
	// ��ǥ��ȯ
	float4x4 mWVP = mul(mWorld, mVP);
	//Out.Pos = mul( Pos, mWVP );
	
	//float4 indices = D3DCOLORtoUBYTE4(BonIndices);
	float4 indices = BonIndices;


	float4 p2;
	float4 p1;
	p1 = mul(Pos, mPalette[ indices.x]);
	p1 *= Weights.x;
	p2 = p1;

	Out.Pos = mul( p2, mWVP );

	
	// ���� ��
	float3 L = -vLightDir;
	float3 N = normalize( mul(Normal, mWIT) ); // ���� ��ǥ�迡���� ����.
	
	Out.Diffuse = I_a * K_a
		 + I_d * K_d * max(0, dot(N,L));

	Out.Tex = Tex;
    
    return Out;
}


// -------------------------------------------------------------
// 1�н�:�ȼ����̴�
// -------------------------------------------------------------
float4 PS_pass0(VS_OUTPUT In) : COLOR
{
	float4 Out;
	//Out = In.Diffuse * tex2D(Samp, In.Tex);
	Out = tex2D(Samp, In.Tex);
	//Out = In.Diffuse;

    return Out;
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

}

