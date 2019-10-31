//=====================================
//
// �����N�C���t�H�A�N�^�[[LinkInfoActor.h]
// �@�\�F�����N���x���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& pos, const int& level):
	InfoActor(pos), linkLevel(level)
{

	// �\�����e
	int d[2];
	d[0] = linkLevel % 10;
	d[1] = linkLevel / 10;
	D3DXVECTOR3 dpos[2];
	dpos[0] = D3DXVECTOR3(192.0f, 128.0f, 0.0f);
	dpos[1] = D3DXVECTOR3(64.0f, 128.0f, 0.0f);
	for (int i = 0; i < 2; i++)
	{
		digitActor[i] = new InfoDigit(d[i], dpos[i]);
	}

}

//=====================================
// �f�X�g���N�^
//=====================================
LinkInfoActor::~LinkInfoActor()
{
	for (int i = 0; i < 2; i++)
	{
		SAFE_DELETE(digitActor[i]);
	}
}

//=====================================
// �X�V
//=====================================
void LinkInfoActor::Update()
{
	for (int i = 0; i < 2; i++)
	{
		digitActor[i]->Update();
	}
}

//=====================================
// �`��
//=====================================
void LinkInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	// ���ƂŃR���g���[���Ɉړ�
	LPDIRECT3DDEVICE9 device = GetDevice();
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	viewer->Begin2D();
	for (int i = 0; i < 2; i++)
	{
		digitActor[i]->Draw();
	}
	viewer->End2D();

	viewer->Draw3D();

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

}

//=====================================
// ���x���ύX���g�p
//=====================================
void LinkInfoActor::SetLevel(const int& nextLevel)
{
	linkLevel = nextLevel;
	//digit[0] = linkLevel % 10;
	//digit[1] = linkLevel / 10;
}
