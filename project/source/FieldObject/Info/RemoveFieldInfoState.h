//=====================================
//
// �����[�u�t�B�[���h�C���t�H�X�e�[�g[RemoveFieldInfoState.h]
// �@�\�F�t�B�[���h�C���t�H�A�N�^�[�̃X�e�[�g�i�쐬�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _REMOVEFIELDINFOSTATE_H_
#define _REMOVEFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// �N���X��`
//**************************************
class FieldInfoActor::RemoveFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity)override;
	State OnUpdate(FieldInfoActor& entity)override;
};

#endif