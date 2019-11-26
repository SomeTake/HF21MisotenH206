//=====================================
//
//FieldCamera.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCAMERA_H_
#define _FIELDCAMERA_H_

#include "../../../Framework/Camera/Camera.h"
#include "../../../Framework/Pattern/BaseState.h"
#include <vector>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldCamera : public Camera
{
public:
	//�J�������[�h��\���񋓎q
	enum Mode
	{
		QuaterView,				//�N�H�[�^�[�r���[���[�h
		FarView,				//���i���[�h
		AngleRotate,			//��]�X�e�[�g
		TransitionOut,			//���x���A�b�v���̈���
		TransitionIn,			//�V�������x���ɂȂ������̏������
		Arround,				//�t�B�[���h�̒��S���œ_�ɂ��ĉ�]�i�^�C�g���A���U���g�j
		Max
	};

	//�R���X�g���N�^�A�f�X�g���N�^
	FieldCamera();
	~FieldCamera();

	//�X�V����
	void Update();

	//���[�h�ؑ֏���
	void ChangeMode(Mode next);

	//�Ǐ]�ڕW�ݒ菈��
	void SetFollowTarget(GameObject* object);

	static const int DurationRotate;
	static const float AnglePeriod;
	static const float LengthFromTarget;
	static const float InitCameraAngle;
	static const float CameraAngleY;

private:
	GameObject *targetObject;						//�Ǐ]�ڕW
	D3DXVECTOR3 startPosition, goalPosition;		//�C�[�W���O�p���W
	int cntFrame;									//�t���[���J�E���g

	float cameraAngle;								//�J������XZ���ʂ̊p�x
	float startAngle, endAngle;						//�C�[�W���O�p�p�x
	int cntRotate;									//��]�t���[���J�E���g

	D3DXVECTOR3 startEyeVector;						//�J�ڊJ�n���̎����x�N�g��

	Mode currentMode;								//���݂̃��[�h
	std::vector<BaseState<FieldCamera, Mode>*> fsm;	//�X�e�[�g�}�V��
	
	//�X�e�[�g�N���X
	class FieldCameraQuater;
	class FieldCameraFar;
	class FieldCameraRotate;
	class FieldCameraTransitionOut;
	class FieldCameraTransitionIn;
	class FieldCameraArround;
};

#endif