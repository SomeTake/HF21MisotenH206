//=====================================
//
//FieldCursor.cpp
//�@�\:�t�B�[���h�J�[�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCursor.h"
#include <algorithm>

/**************************************
�R���X�g���N�^
***************************************/
FieldCursor::FieldCursor() :
	borderX(0.0f), borderZ(0.0f)
{
	//�l�p�`����
	squareContainer.resize(SquareMax);
	for (auto&& square : squareContainer)
	{
		square = new FieldCursorSquare();
	}
}

/**************************************
�f�X�g���N�^
***************************************/
FieldCursor::~FieldCursor()
{
	Utility::DeleteContainer(squareContainer);
}

/**************************************
�X�V����
***************************************/
void FieldCursor::Update()
{
	//30�t���[�������Ɏl�p�`�𔭐�
	if (cntFrame == 0)
	{
		SetSquare();
	}
	Math::WrapAround(0, EmitInterval, ++cntFrame);

	//�l�p�`�X�V
	for (auto&& square : squareContainer)
	{
		square->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void FieldCursor::Draw()
{
	//���g�̃��[���h�ϊ��s����쐬
	D3DXMATRIX mtxWorld = transform->GetMatrix();

	//�l�p�`��`��
	for (auto&& square : squareContainer)
	{
		square->Draw(mtxWorld);
	}
}

/**************************************
�ړ�����
***************************************/
void FieldCursor::Move(const D3DXVECTOR3& direction)
{
	D3DXVECTOR3 position = transform->GetPosition();

	//�ړ��͈͂ɐ�����������
	position.x = Math::Clamp(-borderX, borderX, position.x + direction.x);
	position.z = Math::Clamp(-borderZ, borderZ, position.z + direction.z);

	transform->SetPosition(position);
}

/**************************************
�ړ��͈͐ݒ菈��
***************************************/
void FieldCursor::SetBorder(float borderX, float borderZ)
{
	this->borderX = borderX;
	this->borderZ = borderZ;
}

/**************************************
FieldCursorSquare�Z�b�g����
***************************************/
void FieldCursor::SetSquare()
{
	//��A�N�e�B�u�ȃX�N�G�A��T���ăZ�b�g
	auto itr = std::find_if(squareContainer.begin(), squareContainer.end(), [](auto square)
	{
		return !square->IsActive();
	});

	(*itr)->Set();
}

/**************************************
FieldCursorSquare�R���X�g���N�^
***************************************/
FieldCursorSquare::FieldCursorSquare() :
	cntFrame(FadeDuration)
{
	transform = new Transform();

	//XZ���ʂɑ΂��ĕ��s�ɂȂ�悤�ɉ�]
	transform->Rotate(90.0f, 0.0f, 0.0f);

	//�e�N�X�`���ǂݍ���
	LoadTexture("data/TEXTURE/Field/CursorSquare.png");

	//�T�C�Y�ݒ�
	SetSize(Size);
}

/**************************************
FieldCursorSquare�f�X�g���N�^
***************************************/
FieldCursorSquare::~FieldCursorSquare()
{
	SAFE_DELETE(transform);
}

/**************************************
FieldCursorSquare�X�V����
***************************************/
void FieldCursorSquare::Update()
{
	if (!IsActive())
		return;

	cntFrame++;

	//������Ɉړ�
	transform->Move(Vector3::Up * MoveSpeed);

	//�}�e���A���̓��ߗ���ݒ�
	material.Diffuse.a = 1.0f * cntFrame / FadeDuration;
}

/**************************************
FieldCursorSquare�`�揈��
***************************************/
void FieldCursorSquare::Draw(const D3DXMATRIX& parentMtx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���[���h�ϊ��ݒ�
	transform->SetWorld(&parentMtx);

	//�`��
	BoardPolygon::Draw();
}

/**************************************
FieldCursorSquare�Z�b�g����
***************************************/
void FieldCursorSquare::Set()
{
	cntFrame = 0;
}

/**************************************
FieldCursorSquare�A�N�e�B�u����
***************************************/
bool FieldCursorSquare::IsActive()
{
	return cntFrame < FadeDuration;
}
