//=====================================
//
// �A�C�h���A�N�^�[�X�e�[�g[IdleActorState.cpp]
// �@�\�F�v���C�X�A�N�^�[�̃X�e�[�g�i�ҋ@�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _IDLEACTORSTATE_H_
#define _IDLEACTORSTATE_H_

#include "../PlaceActor.h"

//**************************************
// �N���X��`
//**************************************
class PlaceActor::IdleActorState :
	public PlaceActor::ActorState
{
public:
	void OnStart(PlaceActor& entity)override;
	State OnUpdate(PlaceActor& entity)override;
};

#endif

