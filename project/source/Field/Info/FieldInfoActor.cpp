//=====================================
//
// �t�B�[���h�C���t�H�A�N�^�[[FieldInfoActor.cpp]
// �@�\�F�t�B�[���h��̏���\������A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "FieldInfoActor.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 FieldInfoActor::ActorScale = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

//=====================================
// �R���X�g���N�^
//=====================================
FieldInfoActor::FieldInfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);

	polygon = new BoardPolygon();
	polygon->LoadTexture("data/TEXTURE/Info/Info.png");
	polygon->SetSize(D3DXVECTOR2(ActorScale.x, ActorScale.y));
}

//=====================================
// �f�X�g���N�^
//=====================================
FieldInfoActor::~FieldInfoActor()
{
	SAFE_DELETE(polygon);
}

//=====================================
// �X�V
//=====================================
void FieldInfoActor::Update()
{
	if (!this->IsActive())
		return;;


}

//=====================================
// �`��
//=====================================
void FieldInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	polygon->Draw();

}