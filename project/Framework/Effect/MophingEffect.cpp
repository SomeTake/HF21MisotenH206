//=====================================
//
//MophingEffect.cpp
//�@�\:���[�t�B���O�p�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MophingEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
�R���X�g���N�^
***************************************/
MophingEffect::MophingEffect()
{	
	//�G�t�F�N�g�ǂݍ���
	ResourceManager::Instance()->GetEffect("data/EFFECT/MophingMesh.cfx", effect);

	//�n���h���擾
	hWorld = effect->GetParameterByName(0, "mtxWorld");
	hView = effect->GetParameterByName(0, "mtxView");
	hProjection = effect->GetParameterByName(0, "mtxProjection");

	hMatDiffuse = effect->GetParameterByName(0, "materialDiffuse");
	hMatAmbient = effect->GetParameterByName(0, "materialAmbient");
	hMatSpecular = effect->GetParameterByName(0, "materialSpecular");

	hLightDirection = effect->GetParameterByName(0, "lightDirection");
	hLightDiffuse = effect->GetParameterByName(0, "lightDiffuse");
	hLightAmbient = effect->GetParameterByName(0, "lightAmbient");
	hLightSpecular = effect->GetParameterByName(0, "lightSpecular");

	hTime = effect->GetParameterByName(0, "t");

	hTechnique = effect->GetTechniqueByName("tech");
	effect->SetTechnique(hTechnique);

}

/**************************************
�f�X�g���N�^
***************************************/
MophingEffect::~MophingEffect()
{
	SAFE_RELEASE(effect);
}

/**************************************
�ω������ݒ菈��
***************************************/
void MophingEffect::SetTime(float t)
{
	t = Math::Clamp(0.0f, 1.0f, t);
	effect->SetFloat(hTime, t);
}

/**************************************
���[���h�ϊ��s��ݒ菈��
***************************************/
void MophingEffect::SetWorld(const D3DXMATRIX & mtx)
{
	effect->SetMatrix(hWorld, &mtx);
}
