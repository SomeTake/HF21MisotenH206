//=============================================================================
//
// �΂̕��N���X [ExplosionFlare.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "ExplosionFlare.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	ExplosionFlareController�R���X�g���N�^
	***************************************/
	ExplosionFlareController::ExplosionFlareController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 1.0f, 1.0f };
		const D3DXVECTOR2 DivineTex{ 2.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/ExplosionFlare.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 128;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new ExplosionFlare();
		}

		//�G�~�b�^�[�R���e�i�쐬����
		const unsigned MaxEmitter = 3;
		const int NumEmit = 24;
		const int DurationEmit = 3;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	ExplosionFlare static�����o
	***************************************/
	const int ExplosionFlare::MaxLife = 30;
	const int ExplosionFlare::MinLife = 20;
	const float ExplosionFlare::MaxSpeed = 2.5f;
	const float ExplosionFlare::MinSpeed = 1.5f;

	/**************************************
	ExplosionFlare�R���X�g���N�^
	***************************************/
	ExplosionFlare::ExplosionFlare() :
		AnimationParticle3D(2.0f, 2.0f, MinLife, MaxLife),
		directionMove(Vector3::Random()),
		speedMove(Math::RandomRange(MinSpeed, MaxSpeed))
	{
		directionMove.y = 0.0f;
		D3DXVec3Normalize(&directionMove, &directionMove);
	}

	/**************************************
	ExplosionFlare����������
	***************************************/
	void ExplosionFlare::Init()
	{
		cntFrame = 0;
		active = true;

		//�����_����Z����]
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//�ړ������ɏ������W���I�t�Z�b�g
		transform->Move(directionMove * 2.5f);
	}

	/**************************************
	ExplosionFlare�X�V����
	***************************************/
	void ExplosionFlare::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�o�ߎ��ԂŃA�j���[�V����
		float t = (float)cntFrame / lifeFrame;
		Animation(t);

		//�C�[�W���O�ňړ�
		float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::InOutExpo);
		transform->Move(speed * directionMove);
	}
}