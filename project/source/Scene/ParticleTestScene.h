//=====================================
//
// ParticleTestScene.h
// �@�\:�p�[�e�B�N���e�X�g�V�[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PARTICLETESTSCENE_H_
#define _PARTICLETESTSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

/**************************************
�O���錾
***************************************/
class SkyBox;
class TestParticleManager;
class PlaceActor;
class TestParticleManager;

namespace Field
{
	class FieldGround;
}

/**************************************
�N���X��`
***************************************/
class ParticleTestScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Draw();
	void Update();

private:
	SkyBox *skybox;
	Field::FieldGround *ground;
	PlaceActor *actor;
	TestParticleManager* particleManager;
};

#endif