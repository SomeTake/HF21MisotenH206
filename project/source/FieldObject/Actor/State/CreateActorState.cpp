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

	//Tween::Move(entity, entity.GetPosition() + D3DXVECTOR3(0.0f, 30.0f, 0.0f), entity.GetPosition(), 60, OutCirc);
	Tween::Rotate(entity, entity.ActorScale + D3DXVECTOR3(0.0f, 180.0f, 0.0f), entity.ActorScale, 60, OutCirc);
	Tween::Scale(entity, D3DXVECTOR3(0.0f, 0.0f, 0.0f), entity.ActorScale, 60, OutCirc, [&entity] 
	{
		// �R�[���o�b�N�Ō��݂̃X�e�[�g���A�C�h���ɕύX����Tween���I������
		entity.ChangeState(new IdleActorState());
		//entity.state = Idle;
	});

}

//=====================================
// �X�V����
//=====================================
PlaceActor::State PlaceActor::CreateActorState::OnUpdate(PlaceActor& entity)
{
	return entity.current;
}