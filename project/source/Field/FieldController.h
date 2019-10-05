//=====================================
//
//FieldController.h
//�@�\:�t�B�[���h�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCONTROLLER_H_
#define _FIELDCONTROLLER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseState.h"
#include <vector>

class PlaceModel;

namespace Field
{
	/**************************************
	�O���錾
	***************************************/
	class FieldCursor;
	class FieldGround;
	
	namespace Model
	{
		class PlaceContainer;
	}

	/**************************************
	�N���X��`
	***************************************/
	class FieldController
	{
	public:
		//�t�B�[���h�R���g���[���̃��[�h�񋓎q
		enum State
		{
			Idle,
			BuildRoad,
			UseItem,
			Max
		};

		//�R���X�g���N�^�A�f�X�g���N�^
		FieldController();
		~FieldController();

		//�X�V�A�`�揈��
		void Update();
		void Draw();

		//�f�[�^�ǂݍ��ݏ���
		//TODO:�ǂݍ��ރf�[�^��I���ł���悤�ɂ���
		void Load();

		//���͊m�F����
		void CheckInput();

		//�J�[�\���擾����
		GameObject* GetFieldCursor();

		typedef BaseState<FieldController, FieldController::State> ControllerState;

	private:
		const float PlaceOffset = 10.0f;		//Place��1�}�X���̃I�t�Z�b�g�l
		const int InitFieldBorder = 30;			//�t�B�[���h�͈͂̏����l
		const int InputLongWait = 15;			//���̓��s�[�g�̑ҋ@�t���[��
		const int InputShortWait = 5;			//���̓��s�[�g�̑ҋ@�t���[��

		FieldCursor *cursor;					//�J�[�\��
		FieldGround *ground;					//�n��
		Model::PlaceContainer *placeContainer;	//�v���C�X�R���e�i

		int fieldBorder;						//�t�B�[���h�͈�(�}�X�P��)
		int inputRepeatCnt;						//���͂̃��s�[�g�J�E���g

		ControllerState *state;						//���݂̃X�e�[�g
		std::vector<ControllerState*> fsm;			//�X�e�[�g�}�V��

		//�X�e�[�g�؂�ւ�
		void ChangeState(State next);

		//�e�X�e�[�g�N���X�̑O���錾
		class IdleState;
		class BuildRoadState;
		class UseItemState;
	};
}
#endif