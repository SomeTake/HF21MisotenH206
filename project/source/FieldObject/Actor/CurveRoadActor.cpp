//=====================================
//
// �J�[�u���[�h�A�N�^�[[CurveRoadActor.cpp]
// �@�\�F�J�[�u�p��3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CurveRoadActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "State/CreateActorState.h"

//=====================================
// �R���X�g���N�^
//=====================================
CurveRoadActor::CurveRoadActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("CurveRoad-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::Road;

	// �e�X�g
	state = new CreateActorState();
	state->OnStart(*this);
}

//=====================================
// �f�X�g���N�^
//=====================================
CurveRoadActor::~CurveRoadActor()
{
}
