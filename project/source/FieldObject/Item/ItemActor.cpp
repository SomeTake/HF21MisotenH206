//=====================================
//
// �A�C�e���A�N�^�[[ItemActor.h]
// �@�\�F�A�C�e���̃A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "ItemActor.h"

const D3DXVECTOR2 ItemActor::ActorSize = D3DXVECTOR2(3.0f, 6.0f);
const float ItemActor::RotValue = 1.5f;

//=====================================
// �R���X�g���N�^
//=====================================
ItemActor::ItemActor(const D3DXVECTOR3& pos)
{
	transform = new Transform();
	transform->SetPosition(pos);
	transform->Rotate(0.0f, 0.0f, 0.0f);
	this->SetSize(ActorSize);

	this->LoadTexture("data/TEXTURE/Item/Item.png");

	// �����쐬
	D3DXQUATERNION rot = transform->GetRotation();
	reverse = new ReverseItemActor(transform->GetPosition(), D3DXVECTOR3(rot.x, rot.y, rot.z), ActorSize);
}

//=====================================
// �f�X�g���N�^
//=====================================
ItemActor::~ItemActor()
{
	SAFE_DELETE(transform);
	SAFE_DELETE(reverse);
}

//=====================================
// �X�V
//=====================================
void ItemActor::Update()
{
	this->Rotate(RotValue);
	reverse->Update();
	reverse->Rotate(RotValue);
}

//=====================================
// �`��
//=====================================
void ItemActor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	transform->SetWorld(&mtxWorld);

	BoardPolygon::Draw();

	reverse->Draw();
}

//=====================================
// Y����]
//=====================================
void ItemActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// �R���X�g���N�^
//=====================================
ReverseItemActor::ReverseItemActor(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR2& size)
{
	transform = new Transform();
	transform->SetPosition(D3DXVECTOR3(0.0f, 3.0f, 0.0f));
	transform->Rotate(0.0f, 90.0f, 0.0f);
	this->SetSize(size);

	this->LoadTexture("data/TEXTURE/Item/Item.png");
}

//=====================================
// �f�X�g���N�^
//=====================================
ReverseItemActor::~ReverseItemActor()
{
	SAFE_DELETE(transform);
}

//=====================================
// �X�V
//=====================================
void ReverseItemActor::Update()
{
}

//=====================================
// �`��
//=====================================
void ReverseItemActor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	transform->SetWorld(&mtxWorld);

	BoardPolygon::Draw();
}

//=====================================
// Y����]
//=====================================
void ReverseItemActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}
