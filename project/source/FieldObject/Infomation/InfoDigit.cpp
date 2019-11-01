//=====================================
//
// �C���t�H�f�B�W�b�g[InfoDigit.cpp]
// �@�\�F���\���p����
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "InfoDigit.h"

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const int InfoDigit::divideX = 4;
const int InfoDigit::divideY = 3;
const float InfoDigit::width = 1.0f / divideX;
const float InfoDigit::height = 1.0f / divideY;

//=====================================
// �R���X�g���N�^
//=====================================
InfoDigit::InfoDigit(const int& num, const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	this->num = num;
	this->LoadTexture("data/TEXTURE/Viewer/GameViewer/StockViewer/Number.png");
	this->SetSize(80.0f, 80.0f);

	int x = this->num % divideX;
	int y = this->num / divideX;
	float left = (float)x * width;
	float top = (float)y * height;
	this->SetUV(left, top, width, height);
	this->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=====================================
// �f�X�g���N�^
//=====================================
InfoDigit::~InfoDigit()
{
}

//=====================================
// �X�V
//=====================================
void InfoDigit::Update()
{
}

//=====================================
// �\�����鐔���̕ύX
//=====================================
void InfoDigit::ChangeDigit(const int& num)
{
	this->num = num;
	int x = this->num % divideX;
	int y = this->num / divideX;
	float left = (float)x * width;
	float top = (float)y * height;
	this->SetUV(left, top, width, height);
}