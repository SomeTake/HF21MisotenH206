//=====================================
//
// �����N�C���t�H�A�N�^�[[LinkInfoActor.h]
// �@�\�F�����N���x���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Camera/Camera.h"

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const D3DXVECTOR3 LinkInfoActor::digitPos[] =
{ D3DXVECTOR3(160.0f, 160.0f, 0.0f),
D3DXVECTOR3(96.0f, 160.0f, 0.0f) };
const D3DXVECTOR3 LinkInfoActor::logoPos = D3DXVECTOR3(128.8f, 80.0f, 0.0f);
const D3DXVECTOR2 LinkInfoActor::logoSize = D3DXVECTOR2(100.0f, 100.0f);
const D3DXVECTOR3 LinkInfoActor::upPos[] = { 
	D3DXVECTOR3(-3.0f ,20.0f, 3.0f),
	D3DXVECTOR3(-3.0f ,20.0f, 3.0f),
	D3DXVECTOR3(-3.0f ,10.0f, 3.0f)
};

//=====================================
// �R���X�g���N�^
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& townPos, const int& townLevel, Field::FieldLevel current):
	InfoActor(townPos + upPos[current]), linkLevel(townLevel)
{
	// ���S�\��
	logo = new Polygon2D();
	logo->SetPosition(logoPos);
	logo->LoadTexture("data/TEXTURE/Logo/Logo.png");
	logo->SetSize(logoSize.x, logoSize.y);
	logo->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	logo->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���x���\��
	linkLevel = Math::Clamp(0, 99, linkLevel);
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i] = new InfoDigit(digit[i], digitPos[i]);
	}

}

//=====================================
// �f�X�g���N�^
//=====================================
LinkInfoActor::~LinkInfoActor()
{
	for (int i = 0; i < MaxDigit; i++)
	{
		SAFE_DELETE(digitActor[i]);
	}

	SAFE_DELETE(logo);
}

//=====================================
// �X�V
//=====================================
void LinkInfoActor::Update()
{
	for (int i = 0; i < MaxDigit; i++)
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

	viewer->Begin2D();
	logo->Draw();
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i]->Draw();
	}
	viewer->End2D();

	viewer->Draw3D();

}

//=====================================
// ���x���ύX���g�p
//=====================================
void LinkInfoActor::SetLevel(const int& nextLevel)
{
	if (linkLevel < nextLevel)
	{
		//�J�����̕`��̈�O�Ȃ�G�t�F�N�g�𔭐������Ȃ�
		D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());
		if (screenPos.x >= 0.0f && screenPos.x <= (float)SCREEN_WIDTH
			&& screenPos.y >= 0.0f && screenPos.y <= (float)SCREEN_HEIGHT)
		{
			GameParticleManager::Instance()->Generate(GameParticle::LinkUp, transform->GetPosition());
		}
	}

	linkLevel = nextLevel;
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i]->ChangeDigit(digit[i]);
	}
}

//=====================================
// ���x���擾
//=====================================
int LinkInfoActor::GetLevel()
{
	return linkLevel;
}
