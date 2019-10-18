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

// ���f���\���e�X�g�p
#include "../FieldObject/Actor/PlaceActor.h"

/**************************************
�O���錾
***************************************/
namespace Field
{
	class FieldController;
}

namespace Field::Model
{
	class PlaceModel;
}

class SkyBox;
class FieldCamera;
class TextViewer;
class GameViewer;
class EventController;

/**************************************
�N���X��`
***************************************/
class GameScene : public BaseScene
{
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
		Max
	};

private:
	using SceneState = BaseState<GameScene, State>;

	//�V�[���X�e�[�g�}�V��
	std::vector<SceneState*> fsm;
	State currentState, prevState;

	SkyBox *skybox;								//�w�i�X�J�C�{�b�N�X
	FieldCamera* fieldCamera;					//�t�B�[���h�J����
	Field::FieldController *field;				//�t�B�[���h�R���g���[��
	TextViewer *text;							//�e�X�g�p�e�L�X�g�r���[��
	GameViewer *gameViewer;						//�Q�[���r���A�[
	EventController *eventController;			//�C�x���g�R���g���[���[

	float remainTime;							//�X�e�[�W�̎c�莞��

	//�f���Q�[�^
	DelegatePtr<Route&> onBuildRoad;	//���𐶐������Ƃ��̃f���Q�[�^

	//�X�e�[�g�J�ڏ���
	void ChangeState(State next);

	//�C�x���g�R���g���[���ւ�Place�󂯓n������
	void OnBuildRoad(Route& route);

	//�e�X�e�[�g�N���X
	class GameInit;
	class GameIdle;
	class GameFinish;

	PlaceActor* testActor;
};
#endif