//=====================================
//
// �Z���N�g���S[SelectLogo.cpp]
// �@�\�F�Z���N�g���S
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "SelectLogo.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const float SelectLogo::Distance = 75.0f;
const int SelectLogo::MoveFrame = 15;
const D3DXVECTOR3 SelectLogo::InitLogoPos[] = {
	D3DXVECTOR3(0.0f, 0.0f, -Distance),
	D3DXVECTOR3(Distance * sinf(D3DXToRadian(-60)), 0.0f, Distance * cosf(D3DXToRadian(-60))),
	D3DXVECTOR3(Distance * sinf(D3DXToRadian(60)), 0.0f, Distance * cosf(D3DXToRadian(60)))
};

//=====================================
// �R���X�g���N�^
//=====================================
SelectLogo::SelectLogo() :
	counter(0)
{
	polygon = new BoardPolygon();
}

//=====================================
// �f�X�g���N�^
//=====================================
SelectLogo::~SelectLogo()
{
	SAFE_DELETE(polygon);
}

//=====================================
// �X�V
//=====================================
void SelectLogo::Update()
{

	// �ړ�
	if (moveRight || moveLeft)
	{
		if (counter < MoveFrame)
		{
			// �E��]
			if (moveRight)
			{
				angle -= 120.0f / (float)MoveFrame;
				if (angle <= -180.0f)
				{
					angle += 360.0f;
				}
			}
			// ����]
			else if (moveLeft)
			{
				angle += 120.0f / (float)MoveFrame;
				if (angle >= 180.0f)
				{
					angle -= 360.0f;
				}
			}
			D3DXVECTOR3 curPos = transform->GetPosition();
			curPos.x = Distance * sinf(D3DXToRadian(angle));
			curPos.z = Distance * cosf(D3DXToRadian(angle));
			transform->SetPosition(curPos);
			counter++;
		}
		else
		{
			counter = 0;
			moveRight = false;
			moveLeft = false;
		}
	}
}

//=====================================
// �`��
//=====================================
void SelectLogo::Draw()
{
	polygon->Draw(transform->GetMatrix());
}

//=====================================
// ���\�[�X�ǂݍ���
//=====================================
void SelectLogo::LoadResource(const char * tag)
{
	ResourceManager::Instance()->GetPolygon(tag, polygon);
}

//=====================================
// ���W�Z�b�g
//=====================================
void SelectLogo::SetPosition(const D3DXVECTOR3 & pos)
{
	transform->SetPosition(pos);
}

//=====================================
// �������Z�b�g
//=====================================
void SelectLogo::SetTexDiv(const D3DXVECTOR2& div)
{
	polygon->SetTexDiv(div);
}

//=====================================
// �e�N�X�`���̃Z�b�g
//=====================================
void SelectLogo::SetTextureIndex(const int& index)
{
	polygon->SetTextureIndex(index);
}

//=====================================
// �E�Ɉړ�
//=====================================
void SelectLogo::TurnRight()
{
	if (!Moveable())
		return;
	moveRight = true;
}

//=====================================
// ���Ɉړ�
//=====================================
void SelectLogo::TurnLeft()
{
	if (!Moveable())
		return;
	moveLeft = true;
}

//=====================================
// �ړ��۔���
//=====================================
bool SelectLogo::Moveable()
{
	return counter == 0 ? true : false;
}

//=====================================
// �p�x�̃Z�b�g
//=====================================
void SelectLogo::SetAngle(float angle)
{
	this->angle = angle + 180.0f;
}
