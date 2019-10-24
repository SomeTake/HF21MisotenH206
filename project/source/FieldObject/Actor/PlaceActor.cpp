//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.cpp]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PlaceActor.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../Animation/ActorAnimation.h"
#include "../../../Framework/Camera/ViewFrustrum.h"
#include "../../../Framework/Camera/Camera.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 PlaceActor::ActorScale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// �R���X�g���N�^
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel) :
	onCamera(true)
{
	// ���b�V���R���e�i�̍쐬
	mesh = MeshContainer::Create();

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(pos);
	transform->SetScale(ActorScale);
	this->SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_RELEASE(mesh);
}

//=====================================
// �X�V
//=====================================
void PlaceActor::Update()
{
	// �J�����O����
	onCamera = Camera::MainCamera()->GetViewFrustrum().CheckOnCamera(transform->GetPosition(), 5.0f * sqrtf(2.0f));

#if _DEBUG
	Debug();
#endif
}

//=====================================
// �`��
//=====================================
void PlaceActor::Draw()
{
	if (!this->IsActive())
		return;

	if (!onCamera)
		return;

	transform->SetWorld();
	mesh->Draw();
}

//=====================================
// Y����]
//=====================================
void PlaceActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// ���W�̃Z�b�g
//=====================================
void PlaceActor::SetPosition(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
}

//=====================================
// ���b�V���f�[�^�̃J���[�ύX
//=====================================
void PlaceActor::SetColor(const D3DXCOLOR& color, UINT index)
{
	mesh->SetMaterialColor(color, index);
}

//=====================================
// ���W�A��]�A�傫�������Z�b�g
//=====================================
void PlaceActor::ResetTransform()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	transform->SetScale(ActorScale);
	transform->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=====================================
// �f�o�b�O
//=====================================
#if _DEBUG
void PlaceActor::Debug()
{
	Debug::Begin("PlaceActor", false);
	Debug::Text("ChangeAnimation");
	Debug::NewLine();
	if (Debug::Button("Fall"))
	{
		ActorAnimation::FallAndExpantion(*this);
	}
	Debug::NewLine();
	if (Debug::Button("RotateAndExpantion"))
	{
		ActorAnimation::RotateAndExpantion(*this);
	}
	Debug::NewLine();
	if (Debug::Button("RotateAndShrink"))
	{
		ActorAnimation::RotateAndShrink(*this);
	}
	Debug::NewLine();
	if (Debug::Button("ExpantionYAndReturnToOrigin"))
	{
		ActorAnimation::ExpantionYAndReturnToOrigin(*this);
	}
	Debug::NewLine();
	if (Debug::Button("ResetScale"))
	{
		transform->SetScale(ActorScale);
	}
	Debug::NewLine();
	Debug::Text("OnCamera = %s", onCamera ? "true" : "false");
	if (Debug::Button("OnCamera"))
	{
		onCamera ? onCamera = false : onCamera = true;
	}
	Debug::End();
}
#endif
