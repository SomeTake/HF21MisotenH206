//=====================================
//
//FieldGround.cpp
//�@�\:�t�B�[���h�n��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldGround.h"

/**************************************
�R���X�g���N�^
***************************************/
FieldGround::FieldGround()
{
	LoadTexture("data/TEXTURE/Field/Ground.jpg");
	
	const D3DXVECTOR2 FieldSize{ 10000.0f, 10000.0f };
	const D3DXVECTOR2 TextureLoop{ 500.0f, 500.0f };
	SetSize(FieldSize);
	SetUV(TextureLoop);

	transform->Rotate(90.0f, 0.0f, 0.0f);
}

/**************************************
�f�X�g���N�^
***************************************/
FieldGround::~FieldGround()
{
}

/**************************************
�`�揈��
***************************************/
void FieldGround::Draw()
{
	transform->SetWorld();
	BoardPolygon::Draw();
}
