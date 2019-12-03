//=====================================
//
// �A�`�[�u�r���A�[[AchieveViewer.h]
// �@�\�F�����[�h��B�������Ƃ��ɒʒB���s���r���A�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "AchieveViewer.h"

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const int AchieveViewer::DivideX = 1;
const int AchieveViewer::DivideY = 10;
const float AchieveViewer::SizeX = 480.0f;
const float AchieveViewer::SizeY = 54.0f;
const float AchieveViewer::MoveValue = (SizeY * 2.0f) / 15.0f;
const D3DXVECTOR3 AchieveViewer::InitPosition = D3DXVECTOR3((float)SCREEN_CENTER_X, -SizeY, 0.0f);

//=====================================
// �R���X�g���N�^
//=====================================
AchieveViewer::AchieveViewer() :
	index(0), active(false), cntFrame(0), movePosition()
{
	polygon = new Polygon2D();
	polygon->LoadTexture("data/TEXTURE/Viewer/RewardViewer/Reward.png");
	polygon->SetPosition(D3DXVECTOR3((float)SCREEN_CENTER_X, 0.0f - 108.0f, 0.0f));
	polygon->SetSize(SizeX, SizeY);
	SetIndex(index);
}

//=====================================
// �f�X�g���N�^
//=====================================
AchieveViewer::~AchieveViewer()
{
	SAFE_DELETE(polygon);
}

//=====================================
// �X�V
//=====================================
void AchieveViewer::Update()
{
	if (!active)
		return;

	cntFrame++;
	if (cntFrame < 15)
	{
		movePosition.y += MoveValue;
		polygon->SetPosition(movePosition);
	}
	else if (cntFrame < 45)
	{
	}
	else if (cntFrame < 75)
	{
		movePosition.y -= MoveValue / 2.0f;
		polygon->SetPosition(movePosition);
	}
	else
	{
		active = false;
	}
}

//=====================================
// �`��
//=====================================
void AchieveViewer::Draw()
{
	if (!active)
		return;

	polygon->Draw();
}

//=====================================
// �e�N�X�`���̐؂�ւ�
//=====================================
void AchieveViewer::SetIndex(int index)
{
	this->index = index;
	float top = (1.0f / DivideY) * index;
	float height = 1.0f / DivideY;
	polygon->SetUV(0.0f, top, 1.0f, height);
}

//=====================================
// �A�N�e�B�u�ɂ���
//=====================================
void AchieveViewer::SetActive()
{
	active = true;
	polygon->SetPosition(InitPosition);
	cntFrame = 0;
	movePosition = InitPosition;
}
