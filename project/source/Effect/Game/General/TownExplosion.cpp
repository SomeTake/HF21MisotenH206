//=============================================================================
//
// �����ŃG�t�F�N�g�N���X [TownExplosion.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "TownExplosion.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	TownExplosionController�R���X�g���N�^
	***************************************/
	TownExplosionController::TownExplosionController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 30.0f, 30.0f };
		const D3DXVECTOR2 DivineTex{ 4.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/TownExplosion.png";
		LoadTexture(Path);

		//�G�~�b�^�[�R���e�i�쐬����
		const unsigned MaxParticle = 1;
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;
		const int DurationEmit = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit);
			emitter->CreateParticleContainer<TownExplosion>(MaxParticle);
		}
	}

	/**************************************
	TownExplosion static�����o
	***************************************/
	const int TownExplosion::Life = 20;

	/**************************************
	TownExplosion�R���X�g���N�^
	***************************************/
	TownExplosion::TownExplosion() : AnimationParticle3D(4.0f, 2.0f, Life)
	{

	}

	/**************************************
	TownExplosion����������
	***************************************/
	void TownExplosion::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	TownExplosion�X�V����
	***************************************/
	void TownExplosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�o�ߎ��ԂŃA�j���[�V����
		float t = (float)cntFrame / lifeFrame;
		Animation(t);
	}
}