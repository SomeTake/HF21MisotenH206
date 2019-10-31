#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& pos, const int& level):
	InfoActor(pos), linkLevel(level)
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("LinkInfo", polygon);

	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
	polygon->SetTexDiv(D3DXVECTOR2(4.0f, 3.0f));
}

//=====================================
// �f�X�g���N�^
//=====================================
LinkInfoActor::~LinkInfoActor()
{
	SAFE_DELETE(polygon);
}

//=====================================
// �X�V
//=====================================
void LinkInfoActor::Update()
{
}

//=====================================
// �`��
//=====================================
void LinkInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	D3DXVECTOR3 center = transform->GetPosition();
	D3DXVECTOR3 tyousei[MaxDigit] = { D3DXVECTOR3(-3.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 0.0f, 0.0f) };
	for (int i = 0; i < MaxDigit; i++)
	{
		transform->SetPosition(center + tyousei[i]);
		polygon->SetTextureIndex(digit[i]);
		polygon->Draw(transform->GetMatrix());
	}
	transform->SetPosition(center);
}

// ���x���ύX���g�p
void LinkInfoActor::SetLevel(const int& nextLevel)
{
	linkLevel = nextLevel;
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
}
