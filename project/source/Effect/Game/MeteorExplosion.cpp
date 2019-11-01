//=============================================================================
//
// 覐Δ����G�t�F�N�g�N���X [MeteorExplosion.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "MeteorExplosion.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	MeteorExplosionController�R���X�g���N�^
	***************************************/
	MeteorExplosionController::MeteorExplosionController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 15.0f, 15.0f };
		const D3DXVECTOR2 DivineTex{ 8.0f, 8.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/MeteorExplosion.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new MeteorExplosion();
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
	MeteorExplosion static�����o
	***************************************/
	const int MeteorExplosion::Life = 20;

	/**************************************
	MeteorExplosion�R���X�g���N�^
	***************************************/
	MeteorExplosion::MeteorExplosion() : AnimationParticle3D(8.0f, 8.0f, Life)
	{
	}

	/**************************************
	MeteorExplosion����������
	***************************************/
	void MeteorExplosion::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	MeteorExplosion�X�V����
	***************************************/
	void MeteorExplosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�o�ߎ��ԂŃA�j���[�V����
		float t = (float)cntFrame / lifeFrame;
		Animation(t);
	}
}