//=====================================
//
// UFO�A�N�^�[[UFOActor.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "UFOActor.h"

//=====================================
// �R���X�g���N�^
//=====================================
UFOActor::UFOActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag) :
	EventActorBase(Pos, Scale, MeshTag)
{
}

//=====================================
// �f�X�g���N�^
//=====================================
UFOActor::~UFOActor()
{
}

//=====================================
// �X�V
//=====================================
void UFOActor::Update()
{
	if (InHoverMotion)
	{
		FrameCount++;
		HoverMotion();
	}
}

//=====================================
// �z�o�����O�^���̈ړ��v�Z
//=====================================
void UFOActor::HoverMotion(void)
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
void UFOActor::SetHoverMotion(bool Flag)
{
	InHoverMotion = Flag;
	if (InHoverMotion)
	{
		BaseHoverPos = transform->GetPosition();
	}
}
