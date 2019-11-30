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
	EventInfoEffectController�R���X�g���N�^
	***************************************/
	EventInfoEffectController::EventInfoEffectController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 3.0f, 3.0f };
		const D3DXVECTOR2 Div = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, Div);

		//�e�N�X�`���ǂݍ���
		const char* TexName = "data/TEXTURE/Particle/eventInfo.png";
		LoadTexture(TexName);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 1024;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EventInfoEffect();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 64;
		const int NumEmit = 2;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, 0);
			emitter->UseCulling(true);
		}
	}

	/**************************************
	EventInfoEffect�R���X�g���N�^
	***************************************/
	EventInfoEffect::EventInfoEffect() :
		Particle3D(15, 45)
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

		float offset = Math::RandomRange(-5.0f, 5.0f);
		transform->Move(Vector3::Right * offset);
		transform->Move(Vector3::Forward * offset);
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

		transform->Move(Vector3::Up * 0.3f);
	}

}
