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
float4x4 mtxProjection;
float4 materialDiffuse;
float4 materialAmbient;
float4 materialSpecular;

float4 lightDiffuse[3];
float4 lightAmbient[3];
float4 lightSpecular[3];
float4 lightDirection[3];

float time;

/**************************************
*�e�N�X�`���T���v��
***************************************/
sampler s0 : register(s0);

/**************************************
*���_�V�F�[�_�o�͍\����
***************************************/
struct VS_OUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

/**************************************
*���_�V�F�[�_
***************************************/
VS_OUT VS(
	float3 pos : POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0)
{
	VS_OUT Out = (VS_OUT)0;

	Out.pos = mul(float4(pos, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	Out.uv = float2(0.5f, 0.5f) - uv;

	float3 N = mul(normal, (float3x3)mtxWorld);
	N = normalize(N);

	float4 diffuse = (float4)0;
	float4 ambient = (float4)0;

	for (int i = 0; i < 3; i++)
	{
		float3 L = normalize(-lightDirection[i].xyz);
		diffuse += max(0.0f, dot(L, N)) * lightDiffuse[i];
		ambient += lightAmbient[i];
	}

	Out.color = saturate(diffuse * materialDiffuse + ambient * materialAmbient);

	Out.color.a = 1.0f;

	return Out;
}

/**************************************
*�s�N�Z���V�F�[�_
***************************************/
float4 PS(VS_OUT In) : COLOR0
{
	float distance = length(In.uv);
	float angle = (atan2(In.uv.y, In.uv.x) - 3.141592f) * (1.0f / 6.283814f);

	return tex2D(s0, float2(angle + time, distance + time)) * In.color;
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