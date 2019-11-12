//=====================================
//
//FieldCameraTranslationPlugin.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCAMERATRANSLATIONPLUGIN_H_
#define _FIELDCAMERATRANSLATIONPLUGIN_H_

#include "../../../../main.h"
#include "../FieldCamera.h"
#include "../../../../Framework/Pattern/BaseSingleton.h"
#include <functional>

/**************************************
�N���X��`
***************************************/
class FieldCameraTranslationPlugin : public BaseCameraPlugin, public BaseSingleton<FieldCameraTranslationPlugin>
{
public:
	//����������
	void Init();

	//�X�V����
	void Update();

	//�v���O�C���K�p����
	void Apply(Transform& work);

	//�ړ��J�n����
	//���� position : �ړ���̃J���������_
	//���� duration : �ړ��ɂ�����t���[����
	void Move(const D3DXVECTOR3& position, int duration, std::function<void(void)> callback = nullptr);

	//�ړ��O�̈ʒu�֖߂�����
	//���� duration : �ړ��ɂ�����t���[����
	void Restore(int duration, std::function<void(void)> callback = nullptr);

private:
	enum State
	{
		MoveTowards,
		RestoreBase,
		Idle
	};

	int cntFrame;							//�t���[���J�E���g
	int durationMove;						//�ړ�����
	D3DXVECTOR3 targetPosition;				//�ړ���̖ڕW���W
	State state;							//���݂̃X�e�[�g
	std::function<void(void)> callback;		//�R�[���o�b�N
};

#endif