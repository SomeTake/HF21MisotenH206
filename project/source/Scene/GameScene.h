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

/**************************************
�O���錾
***************************************/
class SkyBox;
class FieldCursor;

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

	FieldCursor *cursor;		//�J�[�\��
	SkyBox *skybox;				//�w�i�X�J�C�{�b�N�X

	//�X�e�[�g�J�ڏ���
	void ChangeState(State next);

	//�e�X�e�[�g�N���X
	class GameInit;
	class GameIdle;
};
#endif