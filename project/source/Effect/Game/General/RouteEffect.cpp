//=====================================
//
//RouteEffect.cpp
//�@�\:���[�g�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "RouteEffect.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	static�����o
	***************************************/
	const float RouteEffect::InitSpeed = 0.08f;

	/**************************************
	RouteEffectController�R���X�g���N�^	
	***************************************/
	RouteEffectController::RouteEffectController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 0.8f, 0.8f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, TexDiv);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/RouteTrace.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new RouteEffect();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 2;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(10, 0);
		}
	}

	/**************************************
	RouteEffect�R���X�g���N�^
	***************************************/
	RouteEffect::RouteEffect() :
		Particle3D(30, 60)
	{

	}

	/**************************************
	RouteEffect����������
	***************************************/
	void RouteEffect::Init()
	{
		cntFrame = 0;
		active = true;

		moveDir = Vector3::Random();

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

		uv.u = Math::RandomRange(0, 2) * 0.5f;
		uv.v = Math::RandomRange(0, 2) * 0.5f;
	}

	/**************************************
	RouteEffect�X�V����
	***************************************/
	void RouteEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(moveDir * InitSpeed);

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);
	}

}

