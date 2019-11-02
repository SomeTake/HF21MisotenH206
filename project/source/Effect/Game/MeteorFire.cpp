//=============================================================================
//
// 覐Ύ���̉��G�t�F�N�g�N���X [MeteorFire.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "MeteorFire.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	MeteorFireController�R���X�g���N�^
	***************************************/
	MeteorFireController::MeteorFireController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 10.0f,10.0f};
		const D3DXVECTOR2 DivineTex{ 3.0f, 1.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/MeteorFire2.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new MeteorFire();
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
	MeteorFire static�����o
	***************************************/
	const int MeteorFire::Life = 300;

	/**************************************
	MeteorFire�R���X�g���N�^
	***************************************/
	MeteorFire::MeteorFire() : AnimationParticle3D(3.0f, 1.0f, Life)
	{
	}

	/**************************************
	MeteorFire����������
	***************************************/
	void MeteorFire::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	MeteorFire�X�V����
	***************************************/
	void MeteorFire::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�o�ߎ��ԂŃA�j���[�V����
		AnimIndex++;
		Animation(AnimIndex / 3);
	}
}