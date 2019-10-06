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
#include "Place\PlaceConfig.h"

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
		class OperatePlaceContainer;
	}

	using PlaceVector = std::vector<Model::PlaceModel*>;
	using PlaceIterator = PlaceVector::iterator;
	using ReversePlaceIterator = std::reverse_iterator<PlaceIterator>;

	/**************************************
	�N���X��`
	***************************************/
	class FieldController
	{
	public:
		//�t�B�[���h�R���g���[���̃��[�h�񋓎q
		enum State
		{
			Idle,			//���ɉ������Ȃ����
			Build,			//���������
			Develop,		//�A�C�e�����g���Đ�A�R���J�񂷂���
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
		static const float PlaceOffset;					//Place��1�}�X���̃I�t�Z�b�g�l
		static const int InitFieldBorder;				//�t�B�[���h�͈͂̏����l
		static const int InputLongWait;					//���̓��s�[�g�̑ҋ@�t���[��
		static const int InputShortWait;				//���̓��s�[�g�̑ҋ@�t���[��
		static const unsigned InitDevelopRiverStock;	//��J���X�g�b�N�̏�����
		static const unsigned InitDevelopMountainStock;	//�R�J���X�g�b�N�̏�����

		FieldCursor *cursor;								//�J�[�\��
		FieldGround *ground;								//�n��

		Model::PlaceContainer *placeContainer;				//�v���C�X�R���e�i
		Model::OperatePlaceContainer *operateContainer;		//����Ώۃv���C�X�̃R���e�i
		Model::RouteContainer routeContainer;				//���[�g���f���R���e�i

		int fieldBorder;						//�t�B�[���h�͈�(�}�X�P��)
		int inputRepeatCnt;						//���͂̃��s�[�g�J�E���g
		unsigned stockDevelopRiver;				//��J���A�C�e���X�g�b�N
		unsigned stockDevelopMountain;			//�R�J���A�C�e���X�g�b�N

		State current;
		ControllerState *state;					//���݂̃X�e�[�g
		std::vector<ControllerState*> fsm;		//�X�e�[�g�}�V��

		//�X�e�[�g�؂�ւ�
		void ChangeState(State next);

		//�J�[�\���ʒu�̃v���C�X���擾
		Model::PlaceModel* GetPlace();

		//�������
		void BuildRoad();

		//��A�R�̊J��
		void DevelopPlace(PlaceVector& route, PlaceIterator start);
		PlaceIterator DevelopMountain(PlaceVector& route, PlaceIterator moutain);
		PlaceIterator DevelopRiver(PlaceVector& route, PlaceIterator river);

		//�e�X�e�[�g�N���X�̑O���錾
		class IdleState;
		class BuildRoadState;
		class UseItemState;
	};
}
#endif