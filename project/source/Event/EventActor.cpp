//=====================================
//
// �C�x���g�A�N�^�[[EventActor.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "EventActor.h"
#include "../../Framework/Camera/ViewFrustum.h"
#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Resource/ResourceManager.h"


//=====================================
// �R���X�g���N�^
//=====================================
EventActor::EventActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag)
{
	// ���b�V���R���e�i�̍쐬
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh(MeshTag, mesh);

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(Pos);
	transform->SetScale(Scale);
	SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
EventActor::~EventActor()
{
	SAFE_DELETE(mesh);
}

//=====================================
// �X�V
//=====================================
void EventActor::Update()
{
	if (InHoverMotion)
	{
		FrameCount++;
		HoverMotion();
	}
}

//=====================================
// �`��
//=====================================
void EventActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y����]
//=====================================
void EventActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// ���W�̃Z�b�g
//=====================================
void EventActor::SetPosition(const D3DXVECTOR3& Pos)
{
	transform->SetPosition(Pos);
}

//=====================================
// �z�o�����O�^���̈ړ��v�Z
//=====================================
void EventActor::HoverMotion(void)
{
	// �^���͈�
	D3DXVECTOR3 Radius = D3DXVECTOR3(0.6f, 0.6f, 0.5f);
	D3DXVECTOR3	Offset = D3DXVECTOR3(20.0f, 10.0f, 30.0f);
	// �^�����x
	D3DXVECTOR3	Rate = D3DXVECTOR3(3.0f, 5.0f, 5.0f);
	D3DXVECTOR3	Theta = D3DXVECTOR3
	(
		D3DXToRadian(Rate.x * FrameCount + Offset.x),
		D3DXToRadian(Rate.y * FrameCount + Offset.y),
		D3DXToRadian(Rate.z * FrameCount + Offset.z)
	);

	D3DXVECTOR3 hover = D3DXVECTOR3
	(
		Radius.x * sinf(Theta.x),
		Radius.y * sinf(Theta.y),
		Radius.z * sinf(Theta.z)
	);

	transform->SetPosition(BaseHoverPos + hover);
}

//=====================================
// �z�o�����O�^���t���O�ݒu
//=====================================
void EventActor::SetHoverMotion(bool Flag)
{
	InHoverMotion = Flag;
	if (InHoverMotion)
	{
		BaseHoverPos = transform->GetPosition();
	}
}
