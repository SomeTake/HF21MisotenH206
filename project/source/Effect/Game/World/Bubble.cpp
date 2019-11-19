//=============================================================================
//
// �A�G�t�F�N�g�N���X [Bubble.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "Bubble.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	BubbleController�R���X�g���N�^
	***************************************/
	BubbleController::BubbleController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 ParticleSize{ 1.0f, 1.0f};
		MakeUnitBuffer(ParticleSize);

		//�e�N�X�`���ǂݍ���
		const char* path = "data/TEXTURE/Particle/Bubble.png";
		LoadTexture(path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new Bubble();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 1;
		const int NumEmit = 64;
		const int DurationEmit = 90;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	Bubble static�����o
	***************************************/
	const int Bubble::MaxLife = 15;
	const int Bubble::MinLife = 5;
	const float Bubble::MinSpeed = 0.4f;
	const float Bubble::MaxSpeed = 0.1f;

	/**************************************
	Bubble�R���X�g���N�^
	***************************************/
	Bubble::Bubble() :
		Particle3D(MinLife, MaxLife),
		Speed(Math::RandomRange(MinSpeed, MaxSpeed)),
		Scale(Math::RandomRange(0.1f, 1.0f))
	{

	}

	/**************************************
	Bubble����������
	***************************************/
	void Bubble::Init()
	{
		cntFrame = 0;
		active = true;

		//�����ʒu���ړ������փI�t�Z�b�g
		float BaseAngle = 10.0f;
		float Theta = Math::RandomRange(0, 36) * BaseAngle;
		float Length = Math::RandomRange(0.0f, 15.0f);
		D3DXVECTOR3 InitOffset = D3DXVECTOR3
		(
			Length * cosf(D3DXToRadian(Theta)),
			Math::RandomRange(0.0f, 1.0f),
			Length * sinf(D3DXToRadian(Theta))
		);
		transform->Move(InitOffset);

		//�X�P�[�����O
		transform->SetScale({ Scale, Scale, 1.0f });
	}

	/**************************************
	Bubble�X�V����
	***************************************/
	void Bubble::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(Vector3::Up * Speed);
	}
}