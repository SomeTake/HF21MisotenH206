//=====================================
//
//LinkLevelUp.cpp
//�@�\:�����N���x���A�b�v����2D�p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "LinkLevelUp.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	LinkLevelUpController::LinkLevelUpController() :
		BaseParticleController(Particle_2D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle = { 100.0f, -100.0f };
		const D3DXVECTOR2 DivParticle = { 4.0f, 4.0f };
		MakeUnitBuffer(SizeParticle, DivParticle);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/levelup.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new LinkLevelUp();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 32;
		const int DurationEmit = 5;
		const int NumEmit = 30;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	LinkLevelUp�R���X�g���N�^
	***************************************/
	LinkLevelUp::LinkLevelUp() :
		Particle2D(20, 45),
		speed(Math::RandomRange(10.0f, 45.0f)),
		initScale(Math::RandomRange(0.2f, 1.0f)),
		directionMove(Vector3::Random())
	{
		directionMove.z = 0.0f;
		directionMove = Vector3::Normalize(directionMove);
	}

	/**************************************
	LinkLevelUp�f�X�g���N�^
	***************************************/
	LinkLevelUp::~LinkLevelUp()
	{
	}

	/**************************************
	LinkLevelUp����������
	***************************************/
	void LinkLevelUp::Init()
	{
		cntFrame = 0;
		active = true;

		int randomIndex = Math::RandomRange(0, 16);
		uv.u = randomIndex % 4 / 4.0f;
		uv.v = randomIndex / 4 / 4.0f;

		transform->Move(directionMove * 30.0f);
	}

	/**************************************
	LinkLevelUp�X�V����
	***************************************/
	void LinkLevelUp::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InCubic);
		transform->SetScale(Vector3::One * scale);

		transform->Move(speed * directionMove);
	}
}