//=====================================
//
//MophingTestScene.h
//�@�\:���[�t�B���O�e�X�g�V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MOPHINGTESTSCENE_H_
#define _MOPHINGTESTSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class MophingEffect;
class MeshContainer;
class MorphingMeshContainer;

namespace Field
{
	class FieldSkyBox;
}
/**************************************
�N���X��`
***************************************/
class MophingTestScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Field::FieldSkyBox *skybox;

	MorphingMeshContainer *morphContainer;
	MeshContainer *mesh;
};
#endif