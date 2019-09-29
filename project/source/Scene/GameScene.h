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

/**************************************
�O���錾
***************************************/
class TransformObject;

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

private:
	TransformObject *object;
};
#endif