//=====================================
//
//EventCamera.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EventCamera.h"
#include "FieldCamera.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
�R���X�g���N�^
***************************************/
EventCamera::EventCamera() :
	referencePosition(Vector3::Zero),
	cntMove(0),
	durationMove(0),
	flgLookAt(false),
	targetObject(nullptr)
{
}

/**************************************
�f�X�g���N�^
***************************************/
EventCamera::~EventCamera()
{
}

/**************************************
����������
***************************************/
void EventCamera::Init()
{
	//���݂̃��C���J�����̃p�����[�^���R�s�[
	*this = *Camera::mainCamera;

	//���̃J�������L���b�V��
	defaultMainCamera = Camera::mainCamera;

	//���g�����C���J�����ɃZ�b�g
	Camera::SetMainCamera(this);

	//�p�����[�^������
	int cntMove = durationMove = 0;
}

/**************************************
��������
***************************************/
void EventCamera::Restore()
{
	//���̃��C���J�����ɖ߂�
	Camera::SetMainCamera(defaultMainCamera);

	//�^�[�Q�b�g������
	targetObject = nullptr;
}

/**************************************
�X�V����
***************************************/
void EventCamera::Update()
{
	//�ړ�����
	if (cntMove < durationMove)
	{
		cntMove++;
		float t = (float)cntMove / durationMove;
		D3DXVECTOR3 position = Easing::EaseValue(t, startPosition, endPosition, EaseType::OutCubic);
		transform->SetPosition(position);

		if (cntMove == durationMove && callback != nullptr)
			callback();
	}

	if (targetObject != nullptr)
	{
		transform->LookAt(targetObject->GetPosition());
	}

	Camera::Update();
}

/**************************************
�ړ��ݒ菈��
***************************************/
void EventCamera::Move(const D3DXVECTOR3 & position, int duration, float eyeDistance, std::function<void()> callback)
{
	flgLookAt = true;
	cntMove = 0;
	durationMove = duration;
	startPosition = transform->GetPosition();
	endPosition = position;
	this->callback = callback;

	referencePosition = transform->Forward() * eyeDistance + transform->GetPosition();
}

/**************************************
���s�ړ�����
***************************************/
void EventCamera::Translation(const D3DXVECTOR3 & position, int duration, std::function<void()> callback)
{
	float angleY = D3DXToRadian(FieldCamera::CameraAngleY);
	float angleXZ = D3DXToRadian(FieldCamera::InitCameraAngle);

	D3DXVECTOR3 offset = D3DXVECTOR3(
		cosf(angleY) * cosf(angleXZ),
		sinf(angleY),
		cosf(angleY) * sinf(angleXZ)) * FieldCamera::LengthFromTarget;

	flgLookAt = false;
	cntMove = 0;
	durationMove = duration;
	startPosition = transform->GetPosition();
	endPosition = position + offset;
	this->callback = callback;
}

/**************************************
���̈ʒu�ɖ߂鏈��
***************************************/
void EventCamera::Return(int duration, std::function<void()> callback)
{
	flgLookAt = false;
	cntMove = 0;
	durationMove = duration;
	startPosition = transform->GetPosition();
	endPosition = defaultMainCamera->GetTransform().GetPosition();
	this->callback = callback;
}

/**************************************
������Z�q
***************************************/
EventCamera & EventCamera::operator=(const Camera & rhs)
{
	Camera* downThis = dynamic_cast<Camera*>(this);
	*downThis = rhs;
	return *this;
}

/**************************************
�^�[�Q�b�g�w��
***************************************/
void EventCamera::SetTargetObject(GameObject * target)
{
	targetObject = target;
}
