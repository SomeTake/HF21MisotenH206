//=====================================
//
// �N���G�C�g�A�N�^�[�X�e�[�g[CreateActorState.h]
// �@�\�F�v���C�X�A�N�^�[�̃X�e�[�g�i�쐬�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _CREATEACTORSTATE_H_
#define _CREATEACTORSTATE_H_

#include "../PlaceActor.h"

//**************************************
// �N���X��`
//**************************************
class PlaceActor::CreateActorState :
	public PlaceActor::ActorState
{
	friend class Tween;
public:
	void OnStart(PlaceActor& entity)override;
	State OnUpdate(PlaceActor& entity)override;
};

#endif
