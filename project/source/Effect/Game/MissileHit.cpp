//=============================================================================
//
// �~�T�C�������G�t�F�N�g�N���X [MissileHit.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "MissileHit.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	MissileHitController�R���X�g���N�^
	***************************************/
	MissileHitController::MissileHitController()
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 15.0f, 15.0f };
		const D3DXVECTOR2 DivineTex{ 8.0f, 8.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/MissileHit.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new MissileHit();
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
	MissileHit static�����o
	***************************************/
	const int MissileHit::Life = 20;

	/**************************************
	MissileHit�R���X�g���N�^
	***************************************/
	MissileHit::MissileHit() : AnimationParticle(8.0f, 8.0f, Life)
	{
	}

	/**************************************
	MissileHit����������
	***************************************/
	void MissileHit::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	MissileHit�X�V����
	***************************************/
	void MissileHit::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�o�ߎ��ԂŃA�j���[�V����
		float t = (float)cntFrame / lifeFrame;
		Animation(t);
	}
}