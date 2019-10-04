//=====================================
//
// �V�e�B�A�N�^�[[CityActor.cpp]
// �@�\�F�s�s�i���A���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CityActor.h"
#include "../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
CityActor::CityActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case FModel::City:
		//ResourceManager::Instance()->GetMesh("City-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}
}

//=====================================
// �f�X�g���N�^
//=====================================
CityActor::~CityActor()
{
}

//=====================================
// �X�V
//=====================================
void CityActor::Update()
{
	if (!IsActive())
		return;

	if (!animActive)
		return;

	switch (animType)
	{
	case FActor::Create:
		break;
	case FActor::Remove:
		break;
	default:
		break;
	}
}