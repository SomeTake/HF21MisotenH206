//=====================================
//
// �A�C�h���t�B�[���h�C���t�H�X�e�[�g[IdleFieldInfoState.h]
// �@�\�F�t�B�[���h�C���t�H�A�N�^�[�̃X�e�[�g�i�ҋ@�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _IDLEFIELDINFOSTATE_H_
#define _IDLEFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// �N���X��`
//**************************************
class FieldInfoActor::IdleFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity);
	State OnUpdate(FieldInfoActor& entity);
};

#endif