//=====================================
//
//SpaceGridEffect.cpp
//�@�\:�F���O���b�h�̕`��G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SpaceGridEffect.h"
#include "../../Framework/Resource/ResourceManager.h"

/**************************************
�R���X�g���N�^
***************************************/
SpaceGridEffect::SpaceGridEffect() :
	SpriteEffect("data/Effect/SpaceGridRenderer.cfx")
{
	//�n���h���擾
	hTime = effect->GetParameterByName(0, "time");
	hLumineTex = effect->GetParameterByName(0, "Lumine");

	//�e�N�X�`���ǂݍ���
	ResourceManager::Instance()->GetTexture("data/TEXTURE/Field/spaceGridLumine.jpg", lumineMap);
	effect->SetTexture(hLumineTex, lumineMap);
}

/**************************************
�f�X�g���N�^
***************************************/
SpaceGridEffect::~SpaceGridEffect()
{
	SAFE_RELEASE(effect);
}

/**************************************
�A���t�@�l�ݒ菈��
***************************************/
void SpaceGridEffect::SetAlpha(float alpha)
{
	diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}

/**************************************
���Ԑݒ菈��
***************************************/
void SpaceGridEffect::SetTime(float t)
{
	effect->SetFloat(hTime, t);
}
