//=====================================
//
//FieldGround.cpp
//�@�\:�t�B�[���h�n��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldGround.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

namespace Field
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldGround::FieldGround()
	{
		ResourceManager::Instance()->MakePolygon("FieldGround", "data/TEXTURE/Field/ground.jpg", { 1000.0f, 1000.0f }, { 500.0f, 500.0f });
		polygon = new BoardPolygon();
		
		ResourceManager::Instance()->GetPolygon("FieldGround", polygon);

		transform->Rotate(90.0f, 0.0f, 0.0f);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	FieldGround::~FieldGround()
	{
		SAFE_DELETE(polygon);
	}

	/**************************************
	�`�揈��
	***************************************/
	void FieldGround::Draw()
	{
		polygon->Draw(transform->GetMatrix());
	}
}