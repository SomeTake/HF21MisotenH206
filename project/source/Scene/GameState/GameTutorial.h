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
	virtual State OnUpdate(GameScene& entity) override;
	virtual void OnStart(GameScene& entity) override;
};
#endif