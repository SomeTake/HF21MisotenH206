//=====================================
//
// Planet�A�N�^�[[PlanetActor.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "PlanetActor.h"
#include "../../../Framework/Particle/BaseEmitter.h"

#if _DEBUG
#include "../../Effect/TestParticleManager.h"
#endif

//=====================================
// �R���X�g���N�^
//=====================================
PlanetActor::PlanetActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag) :
	EventActorBase(Pos, Scale, MeshTag)
{
#if _DEBUG
	MoveTailEmitter = TestParticleManager::Instance()->Generate(TestParticle::MoveTail, Vector3::Zero);
#endif
}

//=====================================
// �f�X�g���N�^
//=====================================
PlanetActor::~PlanetActor()
{
}

//=====================================
// �X�V
//=====================================
void PlanetActor::Update()
{
#if _DEBUG
	FrameCount++;
	HoverMotion();
#endif
}


//=====================================
// �z�o�����O�^���̈ړ��v�Z
//=====================================
void PlanetActor::HoverMotion(void)
{
	float Rate = 5.0f;
	float Theta = D3DXToRadian(Rate * FrameCount);

	D3DXVECTOR3 Pos = D3DXVECTOR3
	(
		10.0f * cosf(Theta),
		10.0f,
		10.0f * sinf(Theta)
	);

	MoveTailEmitter->SetPosition(Pos);
	transform->SetPosition(Pos);
}