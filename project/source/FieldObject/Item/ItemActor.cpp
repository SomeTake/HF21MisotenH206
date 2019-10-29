//=====================================
//
// �A�C�e���A�N�^�[[ItemActor.h]
// �@�\�F�A�C�e���̃A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "ItemActor.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Resource/ResourceManager.h"

const D3DXVECTOR2 ItemActor::ActorSize = D3DXVECTOR2(3.0f, 6.0f);
const float ItemActor::RotValue = 1.5f;

//=====================================
// �R���X�g���N�^
//=====================================
ItemActor::ItemActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->Rotate(0.0f, 0.0f, 0.0f);

	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("ItemActor", polygon);

	//this->SetSize(ActorSize);
	//this->LoadTexture("data/TEXTURE/Item/Item.png");
}

//=====================================
// �f�X�g���N�^
//=====================================
ItemActor::~ItemActor()
{
	SAFE_DELETE(polygon);
}

//=====================================
// ������
//=====================================
void ItemActor::Init()
{
	ResourceManager::Instance()->MakePolygon("ItemActor", "data/TEXTURE/Item/Item.png", ActorSize);
}

//=====================================
// �X�V
//=====================================
void ItemActor::Update()
{
	this->Rotate(RotValue);
}

//=====================================
// �`��
//=====================================
void ItemActor::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���ʂ��`�悵�����̂Ŕw�ʃJ�����O��؂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	polygon->Draw(transform->GetMatrix());

	//�w�ʃJ�����O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=====================================
// Y����]
//=====================================
void ItemActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}