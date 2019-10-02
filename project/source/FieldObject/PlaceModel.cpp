//=====================================
//
// �v���C�X���f��[PlaceModel.cpp]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g���Ǘ�����N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PlaceModel.h"
#include "PlaceActor.h"

using namespace std;

//=====================================
// �R���X�g���N�^
//=====================================
PlaceModel::PlaceModel()
{
	actor.reserve(10000);

	// �Ƃ肠����1�\��
	actor.push_back(new PlaceActor(D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
}

//=====================================
// �f�X�g���N�^
//=====================================
PlaceModel::~PlaceModel()
{
	for (auto &a : actor)
	{
		SAFE_DELETE(a);
	}
	actor.clear();
}

//=====================================
// �X�V
//=====================================
void PlaceModel::Update()
{
	for (auto &a : actor)
	{
		a->Update();
	}
}

//=====================================
// �`��
//=====================================
void PlaceModel::Draw()
{
	for (auto &a : actor)
	{
		a->Draw();
	}
}