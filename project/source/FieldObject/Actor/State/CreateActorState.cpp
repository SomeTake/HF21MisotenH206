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
	entity.current = Create;
}

//=====================================
// �X�V����
//=====================================
PlaceActor::State PlaceActor::CreateActorState::OnUpdate(PlaceActor& entity)
{
	return entity.current;
}