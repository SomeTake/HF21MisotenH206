//=====================================
//
// �Q�[���^�C�g��[GameTitle.h]
// �@�\�F�^�Ct�����
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GAMETITLE_H_
#define _GAMETITLE_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

//**************************************
// �N���X��`
//**************************************
class GameScene::GameTitle :
	public GameScene::SceneState
{
public:
	State OnUpdate(GameScene& entity);
	void OnStart(GameScene& entity);
};

#endif
