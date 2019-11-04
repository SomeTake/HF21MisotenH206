//=====================================
//
//���b�V���C���X�^���V���O�p�̃G�t�F�N�g����[InstancingMeshEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "InstancingMeshEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
�R���X�g���N�^
***************************************/
InstancingMeshRenderer::InstancingMeshRenderer()
{
	//�G�t�F�N�g�ǂݍ���
	ResourceManager::Instance()->GetEffect("data/EFFECT/InstancingMesh.cfx", effect);

	//�n���h���擾
	hMtxView = effect->GetParameterByName(0, "mtxView");
	hMtxProjection = effect->GetParameterByName(0, "mtxProjection");

	hMaterialDiffuse = effect->GetParameterByName(0, "materialDiffuse");
	hMaterialAmbient = effect->GetParameterByName(0, "materialAmbient");
	hMaterialSpecular = effect->GetParameterByName(0, "materialSpecular");

	hLightDirection = effect->GetParameterByName(0, "lightDirection");
	hLightDiffuse = effect->GetParameterByName(0, "lightDiffuse");
	hLightAmbient = effect->GetParameterByName(0, "lightAmbient");
	hLightSpecular = effect->GetParameterByName(0, "lightSpecular");

	hTechnique = effect->GetTechniqueByName("tech");
	effect->SetTechnique(hTechnique);
}

/**************************************
�f�X�g���N�^
***************************************/
InstancingMeshRenderer::~InstancingMeshRenderer()
{
	SAFE_RELEASE(effect);
}

/**************************************
���C�g�ƃJ�����̕ύX���f����
***************************************/
void InstancingMeshRenderer::CommitLightAndCamera()
{
	//�r���[�A�v���W�F�N�V�����s��ݒ�
	effect->SetMatrix(hMtxView, &mtxView);
	effect->SetMatrix(hMtxProjection, &mtxProjection);

	//���C�g���ݒ�
	effect->SetFloatArray(hLightDirection, (float*)&lightContainer[0].Direction, 3);
	effect->SetFloatArray(hLightDiffuse, (float*)&lightContainer[0].Diffuse, 4);
	effect->SetFloatArray(hLightAmbient, (float*)&lightContainer[0].Ambient, 4);
	effect->SetFloatArray(hLightSpecular, (float*)&lightContainer[0].Specular, 4);
}

/**************************************
�}�e���A���Z�b�g����
***************************************/
void InstancingMeshRenderer::SetMaterial(const D3DMATERIAL9 & material)
{
	effect->GetFloatArray(hMaterialDiffuse, (float*)&material.Diffuse, 4);
	effect->GetFloatArray(hMaterialAmbient, (float*)&material.Ambient, 4);
	effect->GetFloatArray(hMaterialSpecular, (float*)&material.Specular, 4);
}
