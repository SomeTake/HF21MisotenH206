//=====================================
//
// �����[�u�A�N�^�[�X�e�[�g[RemoveActorState.h]
// �@�\�F�v���C�X�A�N�^�[�̃X�e�[�g�i�폜�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _REMOVEACTORSTATE_H_
#define _REMOVEACTORSTATE_H_

#include "../PlaceActor.h"

//**************************************
// �N���X��`
//**************************************
class PlaceActor::RemoveActorState :
	public PlaceActor::ActorState
{
public:
	void OnStart(PlaceActor& entity)override;
	State OnUpdate(PlaceActor& entity)override;
};

#endif
