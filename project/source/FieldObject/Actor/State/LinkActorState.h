//=====================================
//
// �����N�A�N�^�[�X�e�[�g[LinkActorState.h]
// �@�\�F�v���C�X�A�N�^�[�̃X�e�[�g�i�����Ȃ������j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _LINKACTORSTATE_H_
#define _LINKACTORSTATE_H_

#include "../PlaceActor.h"

//**************************************
// �N���X��`
//**************************************
class PlaceActor::LinkActorState :
	public PlaceActor::ActorState
{
public:
	void OnStart(PlaceActor& entity)override;
	State OnUpdate(PlaceActor& entity)override;
};

#endif
