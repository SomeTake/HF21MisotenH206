//=====================================
//
// �����[�u�A�N�^�[�X�e�[�g[RemoveActorState.cpp]
// �@�\�F�v���C�X�A�N�^�[�̃X�e�[�g�i�폜�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "RemoveActorState.h"

//=====================================
// ���ꏈ��
//=====================================
void PlaceActor::RemoveActorState::OnStart(PlaceActor& entity)
{
	entity.current = Remove;
}

//=====================================
// �X�V����
//=====================================
PlaceActor::State PlaceActor::RemoveActorState::OnUpdate(PlaceActor& entity)
{
	return entity.current;
}