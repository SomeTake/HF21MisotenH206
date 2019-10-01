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
	template <class T> vtTemp.swap(actor);
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