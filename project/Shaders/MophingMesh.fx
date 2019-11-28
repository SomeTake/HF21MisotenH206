//=====================================
//
//�C���X�^���V���O���b�V���V�F�[�_[ModelInstancing.fx]
//Author:GP12B332 21 ���ԗY��
//
//=====================================

/**************************************
*�O���[�o���ϐ�
***************************************/
float4x4 mtxWorld;				//���[���h�s��
float4x4 mtxView;				//�r���[�s��
float4x4 mtxProjection;			//�v���W�F�N�V�����s��
float4 materialDiffuse;			//�}�e���A���f�B�t���[�Y
float4 materialAmbient;			//�}�e���A���A���r�G���g
float4 materialSpecular;		//�}�e���A���X�y�L�����[

float4 lightDiffuse[3];			//���C�g�f�B�t���[�Y
float4 lightAmbient[3];			//���C�g�A���r�G���g
float4 lightSpecular[3];		//���C�g�X�y�L����
float4 lightDirection[3];		//���C�g����

float t;						//�ω���

/**************************************
*�e�N�X�`���T���v���[
***************************************/
sampler s0 : register(s0);

/**************************************
*���_�V�F�[�_�o�͍\����
***************************************/
struct VS_OUT {
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD0;
	float4 color : COLOR0;
};

/**************************************
*���_�V�F�[�_
***************************************/
VS_OUT VS(
	float3 pos0 : POSITION0,
	float3 normal0 : NORMAL0,
	float2 uv0 : TEXCOORD0,
	float3 pos1 : POSITION1,
	float3 normal1 : NORMAL1,
	float2 uv1 : TEXCOORD1)
{
	VS_OUT Out = (VS_OUT)0;

	//���_�ϊ�
	float4 position = float4(pos0 * (1.0f - t) + pos1 * t, 1.0f);
	Out.pos = mul(position, mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	//�@�������[���h�ϊ�
	float3 N = mul(normal0 * (1.0f - t) + normal1 * t, (float3x3)mtxWorld);
	N = normalize(N);

	//UV���W���i�[
	if (t < 0.5f)
		Out.uv = uv0;
	else
		Out.uv = uv1;

	//���C�g�ɂ��F���v�Z
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
	return tex2D(s0, In.uv) * In.color;
}

/**************************************
*�e�N�j�b�N
**************************************/
technique tech
{
	pass p0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
};