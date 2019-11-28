//=====================================
//
// �t�B�[���h�J�����A���E���h[FieldCameraArround.h]
// �@�\�F�t�B�[���h�̒��S���œ_�ɂ��ĉ�]����J�����i�^�C�g���A���U���g�p�j
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _FIELDCAMERAARROUND_H_
#define _FIELDCAMERAARROUND_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseState.h"

//**************************************
// �N���X��`
//**************************************
class FieldCamera::FieldCameraArround :
	public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);
};


#endif
