//=====================================
//
//EventInfo.cpp
//�@�\:�C�x���g�C���t�H�p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EventInfo.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	static�����o
	***************************************/
	const int EventInfoEmitter::PeriodEmit = 90;

	/**************************************
	EventInfoEffectController�R���X�g���N�^
	***************************************/
	EventInfoEffectController::EventInfoEffectController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 0.5f, 0.5f };
		const D3DXVECTOR2 Div = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, Div);

		//�e�N�X�`���ǂݍ���
		const char* TexName = "data/TEXTURE/Particle/eventInfo.png";
		LoadTexture(TexName);
		
		//�G�~�b�^�R���e�i�쐬
		//�C�x���g�}�X�̍ő吔
		const unsigned MaxParticle = 64;
		const unsigned MaxEmitter = 128;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EventInfoEmitter();
			emitter->CreateParticleContainer<EventInfoEffect>(MaxParticle);
		}
	}

	/**************************************
	EventInfoEffect�R���X�g���N�^
	***************************************/
	EventInfoEffect::EventInfoEffect() :
		Particle3D(20, 40)
	{

	}

	/**************************************
	EventInfoEffect����������
	***************************************/
	void EventInfoEffect::Init()
	{
		active = true;
		cntFrame = 0;

		initScale = Math::RandomRange(0.8f, 1.5f);

		float offset = Math::RandomRange(-4.0f, 4.0f);
		transform->Move(Vector3::Right * offset);

		offset = Math::RandomRange(-4.0f, 4.0f);
		transform->Move(Vector3::Forward * offset);

		uv.u = 0.5f * Math::RandomRange(0, 2);
		uv.v = 0.5f * Math::RandomRange(0, 2);

		speed = Math::RandomRange(0.05f, 0.3f);
	}

	/**************************************
	EventInfoEffect�X�V����
	***************************************/
	void EventInfoEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(scale * Vector3::One);

		transform->Move(Vector3::Up * speed);
	}

	/**************************************
	EventInfoEffectEmitter�R���X�g���N�^
	***************************************/
	EventInfoEmitter::EventInfoEmitter() :
		BaseEmitter(60, 0)
	{
		UseCulling(true);
	}

	/**************************************
	EventInfoEffectEmitter����������
	***************************************/
	void EventInfoEmitter::Init(const std::function<void()>& callback)
	{
		cntFrame = Math::RandomRange(0, PeriodEmit);
		active = true;
		isFinished = false;
		enableEmit = true;

		for (auto&& particle : particleContainer)
		{
			particle->SetActive(false);
		}
	}

	/**************************************
	EventInfoEffectEmitter�X�V����
	***************************************/
	void EventInfoEmitter::Update()
	{
		if (!active)
			return;

		cntFrame = Math::WrapAround(0, PeriodEmit, ++cntFrame);

		Emit();

		isFinished = true;
		for (auto&& particle : particleContainer)
		{
			if (!particle->IsActive())
				continue;

			isFinished = false;

			particle->Update();
		}

		if (cntFrame == duration && isFinished && callback != nullptr)
		{
			callback();
		}
	}

	/**************************************
	EventInfoEffectEmitter���o����
	***************************************/
	bool EventInfoEmitter::Emit()
	{
		if (cntFrame != 0)
			return true;

		return BaseEmitter::Emit();
	}
}
