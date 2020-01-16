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
#include "FieldConfig.h"
#include "../Viewer/GameScene/ParameterContainer/GameViewerParam.h"
#include "../Viewer/GameScene/ParameterContainer/ResultViewerParam.h"

#include <functional>
#include <vector>

class FieldEventHandler;
class InfoController;
class FieldViewer;

namespace Field
{
	/**************************************
	�O���錾
	***************************************/
	class FieldCursor;
	class FieldGround;
	class FieldSkyBox;
	class Score;

	namespace Model
	{
		class PlaceContainer;
		class OperatePlaceContainer;
		class RouteProcessor;
	}

	namespace Actor
	{
		class PlaceActorController;
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
		using ControllerState = BaseState<FieldController, FieldController::State>;

		//�R���X�g���N�^�A�f�X�g���N�^
		FieldController(Field::FieldLevel level);
		~FieldController();

		//�I�u�W�F�N�g�̍X�V����
		void UpdateObject();

		//���W�b�N�̍X�V����
		void UpdateLogic();

		//�`�揈��
		void Draw();
		void DrawInfo();
		void DrawViewer();

		//�t�B�[���h���x���ݒ菈��
		void SetLevel(Field::FieldLevel level);


		//�N���A����
		void Clear();

		//�f�[�^�ǂݍ��ݏ���
		void Load(int csvNo);

		//���͊m�F����
		void CheckInput();

		//�J�[�\���擾����
		GameObject* GetFieldCursor();

		//�r���[���p�����[�^���ߍ���
		void EmbedViewerParam(GameViewerParam& param);

		//���쐬���̃f���Q�[�^�ݒ菈��
		void SetCallbackBuildRoad(const std::function<void(std::vector<Model::PlaceModel*>&)>& callback);

		//���x���A�b�v����ׂ����ǂ���
		bool ShouldLevelUp();

		//�J������؂�ւ���ׂ����ǂ���
		bool ShouldSwicthCamera() const;
		bool ShouldRotateCamera() const;

		//�|�b�v�A�b�v�̑ҋ@����
		bool ShouldWaitPopup() const;

		//�C�x���g�n���h���ݒ菈��
		void SetEventHandler(::FieldEventHandler& handler);

		// UI�`��۔���
		void SetViewerActive(bool flag);

		// ���U���g��ʗp�̃p�����[�^��ݒ肷��
		void SetResultPara(void);

		// ���U���g��ʗp�̃p�����[�^���擾����
		ResultViewerParam* GetResultPara(void);

		// ��������̐����擾
		int GetRoadNum(void);
		
		// ====================
		// �`���[�g���A���p
		// ====================
		// �`���[�g���A���p�t�B�[���h��ݒu����
		void SetTutorialField(void);

		// �J�񂵂����ǂ����𒲂ׂ�
		bool IsDeveloped(void);

		void SetFarView(bool state);

	private:
		//�����N���X�O���錾
		class FieldDevelopper;
		class FieldInput;

		//static�萔�����o
		static const float PlaceOffset;					//Place��1�}�X���̃I�t�Z�b�g�l
		static const int InitFieldBorder;				//�t�B�[���h�͈͂̏����l
		static const int DevelopmentInterval;			//AI���W���x�����オ��C���^�[�o��
		static const float MaxDevelopmentLevelAI;		//AI���W���x���̍ő�l

		FieldCursor *cursor;								//�J�[�\��
		FieldSkyBox *skybox;								//�X�J�C�{�b�N�X

		Model::PlaceContainer *placeContainer;				//�v���C�X�R���e�i
		Model::OperatePlaceContainer *operateContainer;		//����Ώۃv���C�X�̃R���e�i
		Model::RouteContainer routeContainer;				//���[�g���f���R���e�i
		Model::RouteProcessor *routeProcessor;				//���[�g�v���Z�b�T
		Actor::PlaceActorController* placeActController;	//�v���C�X�A�N�^�[�R���g���[��
		InfoController* infoController;						//�C���t�H���[�V�����R���g���[��
		FieldViewer *viewer;								//�t�B�[���h����\������r���[��
		//Score* score;										//�X�R�A�Ǘ�
		ResultViewerParam ResultPara;						//���U���g��ʗp�̃p�����[�^���Ǘ�����N���X

		FieldDevelopper *developper;						//�t�B�[���h�J���̓����N���X
		FieldInput *input;									//�t�B�[���h���͂̓����N���X

		//���쐬���̃R�[���o�b�N
		std::function<void(std::vector<Model::PlaceModel*>&)> onBuildRoad;

		//�X���Ȃ������Ƃ��̃R�[���o�b�N
		std::function<void(const Model::PlaceModel*, const Model::PlaceModel*)> onConnectTown;

		//�v���C�X�^�C�v���؂�ւ�����Ƃ��̃R�[���o�b�N
		std::function<void(const Model::PlaceModel*)> onChangePlaceType;

		int fieldBorder;						//�t�B�[���h�͈�(�}�X�P��)
		int cntFrame;							//�t���[���J�E���g
		int cntStockRecovery;					//�X�g�b�N�񕜃J�E���g
		float developmentLevelAI;				//AI���W���x��(�����N���x���̗ݐ�)
		float developSpeedBonus;				//���W�X�s�[�h�����{�[�i�X
		bool enableDevelop;						//�J��\���ǂ���
		bool flgWaitPopup;						//�|�b�v�A�b�v�ҋ@���
		bool isViewerActive;					//UI�`��۔���
		//bool TutorialOver;						//�`���[�g���A���I���t���O

		FieldLevel currentLevel;				//���݂̃t�B�[���h���x��

		//�������
		int operationZ;
		int operationX;
		int operationSpace;
		int operationC;

		bool inFarView;

		State current;
		ControllerState *state;					//���݂̃X�e�[�g
		std::vector<ControllerState*> fsm;		//�X�e�[�g�}�V��

		//�X�e�[�g�؂�ւ�
		void ChangeState(State next);

		//�J�[�\���ʒu�̃v���C�X���擾
		Model::PlaceModel* GetPlace();

		//AI���W���x���̌v�Z�A���Z
		void CalcDevelopmentLevelAI();

		//�X���q������
		void OnConnectedTown(const Model::PlaceModel *town, const Model::PlaceModel *gate);

		//�A�g�����e�B�X�\��n�̎擾
		const Model::PlaceModel* GetAtlantisPlace();

		//�����N���x������Info���ɃZ�b�g
		void SetLinkLevelInfo();

		//��������̃Z�b�g
		void SetOperationExplanation();



		// �q���������̐����擾
		int GetTownNum(void);

		//�e�X�e�[�g�N���X�̑O���錾
		class IdleState;
		class BuildRoadState;
		class UseItemState;

		friend class PresenDebugController;
	};
}
#endif