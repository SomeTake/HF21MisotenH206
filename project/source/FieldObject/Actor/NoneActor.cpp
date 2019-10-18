//=====================================
//
// �m���A�N�^�[[NoneActor.cpp]
// �@�\�F�����A�N�^�[���Ȃ���Ԃ�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "NoneActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
NoneActor::NoneActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	ResourceManager::Instance()->GetMesh("NoneActor", mesh);
	type = FModel::None;
}

//=====================================
// �f�X�g���N�^�i���b�V���̊J���͊��N���X�Łj
//=====================================
NoneActor::~NoneActor()
{
}