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
class SkyBox;

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
	TransformObject *object;	//�\���e�X�g�p�I�u�W�F�N�g
	SkyBox *skybox;				//�w�i�X�J�C�{�b�N�X
};
#endif