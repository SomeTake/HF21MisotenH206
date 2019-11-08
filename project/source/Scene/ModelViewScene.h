//=====================================
//
// ModelViewScene.h
// �@�\:���f���m�F�V�[��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MODELVIEWSCENE_H_
#define _MODELVIEWSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"

#include <vector>

/**************************************
�O���錾
***************************************/
class PlaceActor;

namespace Field
{
	class FieldSkyBox;
}

/**************************************
�N���X��`
***************************************/
class ModelViewScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

private:
	std::vector<PlaceActor*> actorContainer;
	Field::FieldSkyBox *skybox;
};

#endif