//=====================================
//
//PresenDebugController.h
//�@�\:�v���[���p�̃f�o�b�O����N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PRESENDEBUGCONTROLLER_H_
#define _PRESENDEBUGCONTROLLER_H_

#include "../../main.h"
#include "../Scene/GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class PresenDebugController
{
public:
	PresenDebugController(GameScene* scene);
	~PresenDebugController();

	void Update();

private:
	GameScene *scene;

	void _RaiseMeteorEvent();
	void _ForceLevelUp();
	void _DecreaseLevelAI();
	void _ForceTimeUp();
};

#endif