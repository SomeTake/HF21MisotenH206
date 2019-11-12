//=====================================
//
//FIeldCamera.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCamera.h"

#include "State/FieldCameraQuater.h"
#include "State/FieldCameraFar.h"
#include "State/FieldCameraRotate.h"

#include "../../../Framework/Input/input.h"

/**************************************
static�����o
***************************************/
const int FieldCamera::DurationRotate = 15;
const float FieldCamera::AnglePeriod = 45.0f;
const float FieldCamera::LengthFromTarget = 70.0f;
const float FieldCamera::InitCameraAngle = -45.0f;
const float FieldCamera::CameraAngleY = 60.0f;
/**************************************
�R���X�g���N�^
***************************************/
FieldCamera::FieldCamera() :
	targetObject(NULL),
	startPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	goalPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), 
	cntFrame(0),
	cameraAngle(InitCameraAngle),
	startAngle(InitCameraAngle),
	endAngle(InitCameraAngle),
	cntRotate(DurationRotate),
	currentMode(Mode::FarView)
{
	//�p�����[�^�ݒ�
	const float CameraAngleXZ = D3DXToRadian(cameraAngle);
	const float CameraAngleY = D3DXToRadian(60.0f);
	const float CameraLength = LengthFromTarget;

	const D3DXVECTOR3 InitPos = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * sinf(CameraAngleXZ)) * CameraLength;

	//�X�e�[�g�}�V���쐬
	fsm.resize(Mode::Max);
	fsm[Mode::QuaterView] = new FieldCameraQuater();
	fsm[Mode::FarView] = new FieldCameraFar();
	fsm[Mode::AngleRotate] = new FieldCameraRotate();
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
	//�X�e�[�g�̍X�V
	fsm[currentMode]->OnUpdate(*this);

	Camera::Update();
}

/**************************************
���[�h�ؑ֏���
***************************************/
void FieldCamera::ChangeMode(Mode next)
{
	currentMode = next;

	fsm[currentMode]->OnStart(*this);
}

/**************************************
�Ǐ]�ڕW�ݒ菈��
***************************************/
void FieldCamera::SetFollowTarget(GameObject * object)
{
	targetObject = object;
}
