//=====================================
//
//PunchEffect.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PunchEffect.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	PunchEffectController�R���X�g���N�^
	**************************************/
	PunchEffectController::PunchEffectController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 0.25f, 0.25f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, TexDiv);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/punchEffect.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new PunchEffect();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 4;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(15, 0);
		}
	}

	/**************************************
	PunchEffect�R���X�g���N�^
	***************************************/
	PunchEffect::PunchEffect() :
		Particle3D(5, 10)
	{

	}

	/**************************************
	PunchEffect����������
	***************************************/
	void PunchEffect::Init()
	{
		cntFrame = 0;
		active = true;

		initScale = Math::RandomRange(0.8f, 1.2f);

		const float OffsetRange = 1.0f;
		transform->Move(transform->Right() * Math::RandomRange(-OffsetRange, OffsetRange));
		transform->Move(transform->Up() * Math::RandomRange(-OffsetRange, OffsetRange));

		transform->SetRotation(Vector3::Zero);

		uv.u = Math::RandomRange(0, 2) * 0.5f;
		uv.v = Math::RandomRange(0, 2) * 0.5f;
	}

	/**************************************
	PunchEffect�X�V����
	***************************************/
	void PunchEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		float scale = Easing::EaseValue(t, initScale, 0.0f, InBack);
		transform->SetScale(scale * Vector3::One);
	}

}
