//=====================================
//
//FIeldCamera.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCamera.h"
#include "FieldCameraQuater.h"
#include "FieldCameraFar.h"
#include "../../../Framework/Input/input.h"

/**************************************
�R���X�g���N�^
***************************************/
FieldCamera::FieldCamera() :
	targetObject(NULL),
	startPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	goalPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), 
	cntFrame(0),
	currentMode(Mode::FarView)
{
	//�p�����[�^�ݒ�
	const float CameraAngleXZ = D3DXToRadian(45.0f);
	const float CameraAngleY = D3DXToRadian(60.0f);
	const float CameraLength = 50.0f;

	const D3DXVECTOR3 InitPos = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	//�X�e�[�g�}�V���쐬
	fsm.resize(Mode::Max);
	fsm[Mode::QuaterView] = new FieldCameraQuater();
	fsm[Mode::FarView] = new FieldCameraFar();
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
���͊m�F
***************************************/
void FieldCamera::CheckInput()
{
	//TODO�F�Q�[���p�b�h����̓��͂ɑΉ�����
	if (Keyboard::GetTrigger(DIK_SPACE))
		ChangeMode();
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