//=====================================
//
//�C�x���g�����G�t�F�N�g����[EventHappen.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EventHappen.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	EventHappenController�R���X�g���N�^
	***************************************/
	EventHappenController::EventHappenController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 1.0f, 1.0f };
		const D3DXVECTOR2 DivTex = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, DivTex);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/eventInfo.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned Maxparticle = 512;
		particleContainer.resize(Maxparticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EventHappen();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 16;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(15, 20);
		}
	}

	/**************************************
	EventHappen�R���X�g���N�^
	***************************************/
	EventHappen::EventHappen() :
		Particle3D(15, 30)
	{
	}

	/**************************************
	EventHappen����������
	***************************************/
	void EventHappen::Init()
	{
		cntFrame = 0;
		active = true;

		initScale = Math::RandomRange(0.8f, 1.5f);

		D3DXVECTOR3 offset = Vector3::Zero;
		offset.x = Math::RandomRange(-5.0f, 5.0f);
		offset.z = Math::RandomRange(-5.0f, 5.0f);
		transform->Move(offset);
	}

	/**************************************
	EventHappen�X�V����
	***************************************/
	void EventHappen::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InCubic);
		transform->SetScale(scale * Vector3::One);

		transform->Move(1.5f * Vector3::Up);
	}
}


