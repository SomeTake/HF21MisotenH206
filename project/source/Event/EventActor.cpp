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
EventActor::EventActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag) :
	onCamera(true)
{
	// ���b�V���R���e�i�̍쐬
	mesh = MeshContainer::Create();
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
	SAFE_RELEASE(mesh);
}

//=====================================
// �X�V
//=====================================
void EventActor::Update()
{
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
// ���b�V���f�[�^�̃J���[�ύX
//=====================================
void EventActor::SetColor(const D3DXCOLOR& Color)
{
	unsigned numMaterial = mesh->GetMaterialNum();

	for (unsigned i = 0; i < numMaterial; i++)
	{
		mesh->SetMaterialColor(Color, i);
	}
}

//=====================================
// ���W�A��]�A�傫�������Z�b�g
//=====================================
void EventActor::ResetTransform()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//transform->SetScale(Scale);
	transform->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
