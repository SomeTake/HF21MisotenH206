//=====================================
//
// �Q�[�����U���g[GameResult.h]
// �@�\�F���U���g���
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GAMERESULT_H_
#define _GAMERESULT_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

//**************************************
// �N���X��`
//**************************************
class GameScene::GameResult : 
	public GameScene::SceneState
{
public:
	State OnUpdate(GameScene& entity);
	void OnStart(GameScene& entity);
};

#endif
