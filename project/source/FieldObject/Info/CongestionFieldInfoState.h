//=====================================
//
// �R���W�F�X�e�B�I���t�B�[���h�C���t�H�X�e�[�g[CongestionFieldInfoState.h]
// �@�\�F�t�B�[���h�C���t�H�A�N�^�[�̃X�e�[�g�i���G���Ă���j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _CONGESTIONFIELDINFOSTATE_H_
#define _CONGESTIONFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// �N���X��`
//**************************************
class FieldInfoActor::CongestionFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity)override;
	State OnUpdate(FieldInfoActor& entity)override;
};

#endif