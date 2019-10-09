//=====================================
//
// �A�C�e�����f��[ItemModel.cpp]
// �@�\�F�t�B�[���h��̃A�C�e�����f��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "ItemModel.h"
#include "ItemActor.h"
#include "../../../main.h"

//=====================================
// �R���X�g���N�^
//=====================================
ItemModel::ItemModel() :
	actor(NULL)
{
	actor = new ItemActor(D3DXVECTOR3(0.0f, 3.0f, 0.0f));
}

//=====================================
// �f�X�g���N�^
//=====================================
ItemModel::~ItemModel()
{
	SAFE_DELETE(actor);
}

//=====================================
// �X�V
//=====================================
void ItemModel::Update()
{
	if (actor != NULL)
	{
		actor->Update();
	}
}

//=====================================
// �`��
//=====================================
void ItemModel::Draw()
{
	if (actor != NULL)
	{
		actor->Draw();
	}
}