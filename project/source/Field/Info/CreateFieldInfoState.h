//=====================================
//
// �N���G�C�g�t�B�[���h�C���t�H�X�e�[�g[CreateFieldInfoState.h]
// �@�\�F�t�B�[���h�C���t�H�A�N�^�[�̃X�e�[�g�i�쐬�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _CREATEFIELDINFOSTATE_H_
#define _CREATEFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// �N���X��`
//**************************************
class FieldInfoActor::CreateFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity);
	State OnUpdate(FieldInfoActor& entity);
};

#endif