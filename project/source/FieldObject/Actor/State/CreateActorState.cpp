//=====================================
//
// �N���G�C�g�A�N�^�[�X�e�[�g[CreateActorState.cpp]
// �@�\�F�v���C�X�A�N�^�[�̃X�e�[�g�i�쐬�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CreateActorState.h"
#include "../../../../Framework/Tween/Tween.h"
#include "IdleActorState.h"

//=====================================
// ���ꏈ��
//=====================================
void PlaceActor::CreateActorState::OnStart(PlaceActor& entity)
{
	Tween::Scale(entity, D3DXVECTOR3(0.0f, 0.0f, 0.0f), entity.ActorScale, 120, OutCirc);
	entity.cntState = 0;
}

//=====================================
// �X�V����
//=====================================
PlaceActor::State PlaceActor::CreateActorState::OnUpdate(PlaceActor& entity)
{
	State current = State::Create;

	entity.cntState++;

	if (entity.cntState == 120)
	{
		entity.ChangeState(new IdleActorState());
		current = State::Idle;
		return current;
	}

	return current;
}