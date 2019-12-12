//=====================================
//
//GameAchieveResult.h
//�@�\:�Q�[���̎��у��U���g���
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEACHIEVERESULT_H_
#define _GAMEACHIEVERESULT_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
�N���X��`
***************************************/
class GameScene::GameAchieveResult : public GameScene::SceneState
{
public:
	void OnStart(GameScene& entity);
	State OnUpdate(GameScene& entity);

	enum Step
	{
		AchieveViewerIn,
		AchieveInputWait,
		AchieveNameEntryWait,
		AchieveNameEntryFinish,
		AchieveViewerOut,
		Transition
	};

private:
	void TransitionToTitle(GameScene& entity);
};
#endif