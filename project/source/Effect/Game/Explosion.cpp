//=============================================================================
//
// �����G�t�F�N�g�N���X [Explosion.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "Explosion.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	ExplosionController�R���X�g���N�^
	***************************************/
	ExplosionController::ExplosionController()
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 30.0f, 30.0f };
		const D3DXVECTOR2 DivineTex{ 4.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/MeteorExplosion.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new Explosion();
		}

		//�G�~�b�^�[�R���e�i�쐬����
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;
		const int DurationEmit = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit);
		}
	}

	/**************************************
	Explosion static�����o
	***************************************/
	const int Explosion::Life = 20;
	const float Explosion::Speed = 3.0f;

	/**************************************
	Explosion�R���X�g���N�^
	***************************************/
	Explosion::Explosion() :
		AnimationParticle(4.0f, 2.0f, Life),
		speedMove(Speed)
	{
	}

	/**************************************
	Explosion����������
	***************************************/
	void Explosion::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	Explosion�X�V����
	***************************************/
	void Explosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�o�ߎ��ԂŃA�j���[�V����
		float t = (float)cntFrame / lifeFrame;
		Animation(t);

		//�C�[�W���O�ňړ�
		//float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::Linear);
		//transform->Move(speed * directionMove);
	}
}