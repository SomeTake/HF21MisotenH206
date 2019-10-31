//=====================================
//
// �C���t�H�A�N�^�[[InfoActor.cpp]
// �@�\�F�t�B�[���h��ɏ���\�����邽�߂̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "InfoActor.h"
#include "../../../Framework/Camera/Camera.h"
#include "../../../Framework/Camera/ViewFrustum.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const float InfoActor::ActorSize = 10.0f;

//=====================================
// �R���X�g���N�^
//=====================================
InfoActor::InfoActor(const D3DXVECTOR3& pos)
{
	transform->SetPosition(pos);
	transform->SetScale(Vector3::One);
	this->SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
InfoActor::~InfoActor()
{
	SAFE_DELETE(polygon);
}

//=====================================
// �X�V
//=====================================
void InfoActor::Update()
{
	if (!this->IsActive())
		return;

	//onCamera = Camera::MainCamera()->GetViewFrustrum().CheckOnCamera(transform->GetPosition(), ActorSize);

}

//=====================================
// �`��
//=====================================
void InfoActor::Draw()
{
	if (!this->IsActive())
		return;

	//if (!onCamera)
	//	return;

	polygon->Draw(transform->GetMatrix());

}
