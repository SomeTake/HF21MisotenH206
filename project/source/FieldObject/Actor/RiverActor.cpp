//=====================================
//
// ���o�[�A�N�^�[[RiverActor.cpp]
// �@�\�F��i����f��j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "RiverActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "State/CreateActorState.h"

//=====================================
// �R���X�g���N�^
//=====================================
RiverActor::RiverActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case FModel::City:
		//ResourceManager::Instance()->GetMesh("River-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::River;

	// �e�X�g
	state = new CreateActorState();
	state->OnStart(*this);
}

//=====================================
// �f�X�g���N�^
//=====================================
RiverActor::~RiverActor()
{
}
