//=============================================================================
//
// �|�[�Y��ʃN���X [GameInterrupt.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _GameInterrupt_H_
#define _GameInterrupt_H_

#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameInterrupt : public BaseState<GameScene, GameScene::State>
{
public:
	virtual State OnUpdate(GameScene& entity) override;
	virtual void OnStart(GameScene& entity) override;
};
#endif