//=====================================
//
//[RiverRenderer.fx]
//RiverActor�`��V�F�[�_
//Author:GP12B332 21 ���ԗY��
//
//=====================================

/**************************************
*�O���[�o���ϐ�
***************************************/
float4x4 mtxWorld;
float4x4 mtxView;
float4x4 mtxProj;
float4 diffuse;
float time;
texture Lumine;

/**************************************
*�e�N�X�`���T���v��
***************************************/
sampler s0 : register(s0);
sampler LumineSampler = sampler_state
{
	Texture = <Lumine>;
	MagFilter = Linear;
	MinFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

/**************************************
*���_�V�F�[�_�o�͍\����
***************************************/
struct VS_OUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

/**************************************
*���_�V�F�[�_
***************************************/
VS_OUT VS(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0)
{
	VS_OUT Out = (VS_OUT)0;

	Out.pos = mul(float4(pos, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	Out.uv = localUV;

	return Out;
}

/**************************************
*�s�N�Z���V�F�[�_
***************************************/
float4 PS(VS_OUT In) : COLOR0
{
	float4 color = tex2D(s0, In.uv) * diffuse;
	
	In.uv /= 50.0f;
	float alpha = tex2D(LumineSampler, In.uv + float2(time, time)).r;
	color.a *= alpha;

	return color;
}

/**************************************
*�e�N�j�b�N
***************************************/
technique tech
{
	pass p0
	{
		ALPHABLENDENABLE = true;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
};