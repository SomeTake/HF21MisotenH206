//=====================================
//
// �R�l�N�g�t�B�[���h�C���t�H�X�e�[�g[ConnectFieldInfoState.h]
// �@�\�F�t�B�[���h�C���t�H�A�N�^�[�̃X�e�[�g�i�����Ȃ������j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _CONNECTFIELDINFOSTATE_H_
#define _CONNECTEFIELDINFOSTATE_H_

#include "FieldInfoActor.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// �N���X��`
//**************************************
class FieldInfoActor::ConnectFieldInfoState :
	public FieldInfoActor::InfoState
{
public:
	void OnStart(FieldInfoActor& entity);
	State OnUpdate(FieldInfoActor& entity);
};

#endif