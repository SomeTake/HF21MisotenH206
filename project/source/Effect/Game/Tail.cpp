//=============================================================================
//
// �ړ��̎c���G�t�F�N�g�N���X [Tail.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "Tail.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	TailController�R���X�g���N�^
	***************************************/
	TailController::TailController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 ParticleSize{ 1.0f, 1.0f };
		MakeUnitBuffer(ParticleSize);

		//�e�N�X�`���ǂݍ���
		const char* path = "data/TEXTURE/Particle/Tail.png";
		LoadTexture(path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new Tail();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;
		const int DurationEmit = 90;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	Tail static�����o
	***************************************/
	const int Tail::Life = 10;

	/**************************************
	Tail�R���X�g���N�^
	***************************************/
	Tail::Tail() :
		Particle3D(Life)
	{
	}

	/**************************************
	Tail����������
	***************************************/
	void Tail::Init()
	{
		cntFrame = 0;
		active = true;

		//�����ʒu���ړ������փI�t�Z�b�g
		//float BaseAngle = 10.0f;
		//float Theta = Math::RandomRange(0, 36) * BaseAngle;
		//float Length = Math::RandomRange(0.0f, 15.0f);
		//D3DXVECTOR3 InitOffset = D3DXVECTOR3
		//(
		//	Length * cosf(D3DXToRadian(Theta)),
		//	Math::RandomRange(0.0f, 1.0f),
		//	Length * sinf(D3DXToRadian(Theta))
		//);
		//transform->Move(InitOffset);

	}

	/**************************************
	Tail�X�V����
	***************************************/
	void Tail::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(Vector3::Right * 2.0f);
	}
}