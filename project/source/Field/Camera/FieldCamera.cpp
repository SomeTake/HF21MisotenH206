//=====================================
//
//FIeldCamera.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FIeldCamera.h"

/**************************************
�R���X�g���N�^
***************************************/
FieldCamera::FieldCamera()
{
	fsm.resize(Mode::Max);
}

/**************************************
�f�X�g���N�^
***************************************/
FieldCamera::~FieldCamera()
{
	Utility::DeleteContainer(fsm);
}

/**************************************
�X�V����
***************************************/
void FieldCamera::Update()
{
	//�Ǐ]�ڕW�̍��W�����_�ɐݒ�
	target = targetObject->GetPosition();

	//�X�e�[�g�̍X�V
	fsm[currentMode]->OnUpdate(*this);

	Camera::Update();
}

/**************************************
���[�h�ؑ֏���
***************************************/
void FieldCamera::ChangeMode()
{
	currentMode = (Mode)Math::WrapAround(Mode::QuaterView, Mode::Max, currentMode + 1);

	fsm[currentMode]->OnStart(*this);
}

/**************************************
�Ǐ]�ڕW�ݒ菈��
***************************************/
void FieldCamera::SetFollowTarget(GameObject * object)
{
	targetObject = object;
}
