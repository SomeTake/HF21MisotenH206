//=====================================
//
// �A�C�h���A�N�^�[�X�e�[�g[IdleActorState.cpp]
// �@�\�F�v���C�X�A�N�^�[�̃X�e�[�g�i�ҋ@�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "IdleActorState.h"

//=====================================
// ���ꏈ��
//=====================================
void PlaceActor::IdleActorState::OnStart(PlaceActor& entity)
{
	entity.current = Idle;
}

//=====================================
// �X�V����
//=====================================
PlaceActor::State PlaceActor::IdleActorState::OnUpdate(PlaceActor& entity)
{
	return entity.current;
}