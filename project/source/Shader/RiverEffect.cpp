//=====================================
//
//RiverEffect.cpp
//�@�\:RiverActor�`��G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "RiverEffect.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Light/Light.h"

namespace Field::Actor
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	RiverEffect::RiverEffect()
	{
		//�G�t�F�N�g
		ResourceManager::Instance()->GetEffect("data/EFFECT/RiverRenderer.cfx", effect);

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

		hTexUV = effect->GetParameterByName(0, "texUV");

		effect->SetTechnique("tech");
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	RiverEffect::~RiverEffect()
	{
		SAFE_RELEASE(effect);
	}

	/**************************************
	���[���h���ݒ菈��
	***************************************/
	void RiverEffect::SetWorld(const Transform & transform)
	{
		D3DXMATRIX mtx = transform.GetMatrix();
		effect->SetMatrix(hWorld, &mtx);
	}

	/**************************************
	�e�N�X�`��UV�ݒ菈��
	***************************************/
	void RiverEffect::SetUV(const D3DXVECTOR2 & uv)
	{
		effect->SetFloatArray(hTexUV, (float*)&uv, 2);
	}
}