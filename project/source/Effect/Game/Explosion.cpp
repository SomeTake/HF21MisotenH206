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
	const int Explosion::Life = 30;
	const float Explosion::Speed = 2.5f;

	/**************************************
	Explosion�R���X�g���N�^
	***************************************/
	Explosion::Explosion() :
		AnimationParticle(4.0f, 2.0f, Life),
		directionMove(Vector3::Zero),
		speedMove(Speed)
	{
		//directionMove.y = 0.0f;
		D3DXVec3Normalize(&directionMove, &directionMove);
	}

	/**************************************
	Explosion����������
	***************************************/
	void Explosion::Init()
	{
		cntFrame = 0;
		active = true;

		//�����_����Z����]
		//transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//�ړ������ɏ������W���I�t�Z�b�g
		transform->Move(directionMove * 2.5f);
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
		float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::Linear);
		transform->Move(speed * directionMove);
	}
}