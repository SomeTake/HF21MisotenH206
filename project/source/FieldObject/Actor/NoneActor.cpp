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
NoneActor::NoneActor()
	: PlaceActor()
{
	// ���f���f�[�^�Q��
	ResourceManager::Instance()->GetMesh("NoneActor", mesh);
	type = Field::Model::None;
}

//=====================================
// �f�X�g���N�^�i���b�V���̊J���͊��N���X�Łj
//=====================================
NoneActor::~NoneActor()
{
}

//=====================================
// �X�V����
//=====================================
void NoneActor::Update()
{
	//�Ƃɂ������������̂ŃJ�����O��؂��ăC���X�^���V���O�ɔC����
}