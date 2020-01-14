//=============================================================================
//
// �`���[�g���A���N���X [GameTutorial.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _GameTutorial_H_
#define _GameTutorial_H_

#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameTutorial : public BaseState<GameScene, GameScene::State>
{
public:
	virtual State OnUpdate(GameScene& entity) override;
	virtual void OnStart(GameScene& entity) override;

	void Init(GameScene& entity);
	void TutorialClear(GameScene& entity);
	
private:
	int FrameCount = 0;
	// �`���[�g���A�����삪�I���t���O
	bool ClearFlag = false;
};
#endif