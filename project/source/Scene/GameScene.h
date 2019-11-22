//=====================================
//
//GameScene.h
//�@�\:�Q�[���V�[������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include "../../Framework/Pattern/BaseState.h"
#include "../../Framework/Pattern/Delegate.h"

#include <vector>

/**************************************
�O���錾
***************************************/
namespace Field
{
	class FieldController;
	class FieldSkyBox;
}

namespace Field::Model
{
	class PlaceModel;
}

class FieldCamera;
class GameViewer;
class EventController;
class GameParticleManager;
class FieldEventHandler;
class BloomController;
class PlaceActor;
class SerialWrapper;
class UDPClient;
class SceneParticleManager;
class GuideViewer;

/**************************************
�N���X��`
***************************************/
class GameScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	using Route = std::vector<Field::Model::PlaceModel*>;

	void Init();
	void Uninit();
	void Update();
	void Draw();

	//�X�e�[�g��\���񋓎q
	enum State
	{
		Initialize,
		Idle,
		Finish,
		LevelUp,
		Pause,
		FarView,
		Title,
		Result,
		TransitionOut,
		TransitionIn,
		Max
	};

	//�X�e�[�g�J�ڏ���
	void ChangeState(State next);

private:
	using SceneState = BaseState<GameScene, State>;

	//�V�[���X�e�[�g�}�V��
	std::vector<SceneState*> fsm;
	State currentState, prevState;

	FieldCamera* fieldCamera;					//�t�B�[���h�J����
	Field::FieldController *field;				//�t�B�[���h�R���g���[��
	GameViewer *gameViewer;						//�Q�[���r���A�[
	EventController *eventController;			//�C�x���g�R���g���[���[
	GameParticleManager *particleManager;		//�p�[�e�B�N���}�l�[�W��
	SceneParticleManager *levelParticleManager;	//���x���ʂ̃p�[�e�B�N���}�l�[�W��
	FieldEventHandler* eventHandler;			//�C�x���g�n���h��
	SerialWrapper *serial;						//�V���A���ʐM
	UDPClient *Client;							//�N���C�A���g
	GuideViewer* guideViewer;					//�K�C�h�r���A�[

	int remainTime;								//��������

	int cntFrame;								//�t���[���J�E���^

	//�|�X�g�G�t�F�N�g�֘A
	BloomController *bloomController;			//�u���[���G�t�F�N�g�̃R���g���[��

	//�f���Q�[�^
	Delegate<void(Route&)> *onBuildRoad;		//���𐶐������Ƃ��̃f���Q�[�^

	//�C�x���g�R���g���[���ւ�Place�󂯓n������
	void OnBuildRoad(Route& route);

	//���x���A�b�v����
	void OnLevelUp();

	//�C�x���g�n���h���ݒ菈��
	void SetEventHandler();

	//�f�o�b�O�@�\
	void DebugTool();

	//�N���A����
	void Clear();

	//static�萔�����o
	static const float BloomPower[3];
	static const float BloomThrethold[3];

	//�e�X�e�[�g�N���X
	class GameInit;
	class GameIdle;
	class GameFinish;
	class GameLevelUp;
	class GamePause;
	class GameFarView;
	class GameWaitPopup;
	class GameTitle;
	class GameResult;
	class GameTransitionOut;
	class GameTransitionIn;

	//�f�o�b�O�p�t�B�[���h���x��
	static int level;
};
#endif