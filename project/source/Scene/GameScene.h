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

class SkyBox;
class FieldCamera;
class TextViewer;
class GameViewer;
class EventController;

//���C�x���g�R���g���[���[���o�����炻�����ړ�
class EventViewer;

/**************************************
�N���X��`
***************************************/
class GameScene : public BaseScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//�X�e�[�g��\���񋓎q
	enum State
	{
		Initialize,
		Idle,
		Max
	};

private:
	//�V�[���X�e�[�g�}�V��
	std::vector<BaseState<GameScene, State>*> fsm;
	State currentState, prevState;

	SkyBox *skybox;								//�w�i�X�J�C�{�b�N�X
	FieldCamera* fieldCamera;					//�t�B�[���h�J����
	Field::FieldController *field;				//�t�B�[���h�R���g���[��
	TextViewer *text;							//�e�X�g�p�e�L�X�g�r���[��
	GameViewer *gameViewer;						//�Q�[���r���A�[

	//���C�x���g�R���g���[���[���o�����炻�����ړ�
	EventViewer *eventViewer;


	EventController *eventController;			// �C�x���g�R���g���[���[
	float remainTime;							//�X�e�[�W�̎c�莞��

	//�X�e�[�g�J�ڏ���
	void ChangeState(State next);

	//�e�X�e�[�g�N���X
	class GameInit;
	class GameIdle;

	PlaceActor* testActor;
};
#endif