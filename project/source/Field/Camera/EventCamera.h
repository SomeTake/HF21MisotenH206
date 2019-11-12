//=====================================
//
//EventCamera.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EVENTCAMERA_H_
#define _EVENTCAMERA_H_

#include "../../../main.h"
#include "../../../Framework/Camera/Camera.h"

#include <functional>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class EventCamera : public Camera
{
public:
	EventCamera();
	~EventCamera();

	//����������
	//�C�x���g�Ŏg�p����O�ɂ��Ȃ炸�Ă�
	void Init();

	//���̃J�������g�p����悤�ɖ߂�
	void Restore();

	//�X�V����
	void Update();

	//�ړ�����
	void Move(const D3DXVECTOR3& position, int duration, std::function<void()> callback = nullptr);

	//���̃J�����̈ʒu�ɖ߂�
	void Return(int duration, std::function<void()> callback = nullptr);

	//������Z�q
	EventCamera& operator=(const Camera& rhs);

private:
	//���̃��C���J����
	Camera *defaultMainCamera;

	//�ړ��C�[�W���O�p�p�����[�^
	int cntMove;
	int durationMove;
	D3DXVECTOR3 startPosition, endPosition;
	std::function<void()> callback;
};
#endif