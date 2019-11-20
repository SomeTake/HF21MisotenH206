//=====================================
//
//WhirlPoolEffect.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "WhirlPoolEffect.h"
#include "../../Framework/Resource/ResourceManager.h"

namespace Field::Actor
{
	/**************************************	
	�R���X�g���N�^
	***************************************/
	WhirlPoolEffect::WhirlPoolEffect()
	{
		//�G�t�F�N�g�ǂݍ���
		ResourceManager::Instance()->GetEffect("data/EFFECT/WhirlPoolRenderer.cfx", effect);

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

		hTime = effect->GetParameterByName(0, "time");

		effect->SetTechnique("tech");
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	WhirlPoolEffect::~WhirlPoolEffect()
	{
		SAFE_RELEASE(effect);
	}

	/**************************************
	���[���h�ϊ��s��ݒ菈��
	***************************************/
	void WhirlPoolEffect::SetWorld(const Transform & transform)
	{
		D3DXMATRIX mtx = transform.GetMatrix();
		effect->SetMatrix(hWorld, &mtx);
	}

	/**************************************
	�o�ߎ��Ԑݒ菈��
	***************************************/
	void WhirlPoolEffect::SetTime(float t)
	{
		effect->SetFloat(hTime, t);
	}
}