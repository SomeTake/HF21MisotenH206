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
		Max
	};

	//�R���X�g���N�^�A�f�X�g���N�^
	FieldCamera();
	~FieldCamera();

	//�X�V����
	void Update();

	//���[�h�ؑ֏���
	void ChangeMode();

	//�Ǐ]�ڕW�ݒ菈��
	void SetFollowTarget(GameObject* object);

private:
	GameObject *targetObject;						//�Ǐ]�ڕW
	D3DXVECTOR3 startPosition, goalPosition;		//�C�[�W���O�p���W

	Mode currentMode;								//���݂̃��[�h
	std::vector<BaseState<FieldCamera, Mode>*> fsm;	//�X�e�[�g�}�V��
	
	//�X�e�[�g�N���X
	class FieldCameraQuater;
	class FieldCameraFar;
};

#endif