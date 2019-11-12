//=====================================
//
//EventCamera.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EventCamera.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
�R���X�g���N�^
***************************************/
EventCamera::EventCamera()
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
		transform.SetPosition(position);
	}

	Camera::Update();
}

/**************************************
�ړ��ݒ菈��
***************************************/
void EventCamera::Move(const D3DXVECTOR3 & position, int duration, std::function<void()> callback)
{
	cntMove = 0;
	durationMove = duration;
	startPosition = transform.GetPosition();
	endPosition = position;
	this->callback = callback;
}

/**************************************
���̈ʒu�ɖ߂鏈��
***************************************/
void EventCamera::Return(int duration, std::function<void()> callback)
{
	cntMove = 0;
	durationMove = duration;
	startPosition = transform.GetPosition();
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
