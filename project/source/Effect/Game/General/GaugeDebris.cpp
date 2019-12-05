//=====================================
//
//GaugeDebris.cpp
//�@�\:�Q�[�W�̔j�Ѓp�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GaugeDebris.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	GaugeDebrisController�R���X�g���N�^
	***************************************/
	GaugeDebrisController::GaugeDebrisController() :
		BaseParticleController(Particle_2D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 80.0f, -80.0f };
		const D3DXVECTOR2 TexDiv = {2.0f, 2.0f};
		MakeUnitBuffer(Size, TexDiv);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/gaugeDebris.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new GaugeDebris();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 16;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(60, 3);
		}
	}

	/**************************************
	GaudeDebris�R���X�g���N�^
	***************************************/
	GaugeDebris::GaugeDebris() :
		Particle2D(15, 30)
	{
	}

	/**************************************
	GaugeDebris����������
	***************************************/
	void GaugeDebris::Init()
	{
		active = true;
		cntFrame = 0;

		speed = Math::RandomRange(20.0f, 50.0f);

		moveDir = Vector3::Random();
		moveDir.z = 0.0f;
		moveDir.x = fabsf(moveDir.x);

		initScale = Math::RandomRange(0.5f, 1.8f);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

		uv.u = Math::RandomRange(0, 2) * 0.5f;
		uv.v = Math::RandomRange(0, 2) * 0.5f;

		D3DXVECTOR3 offset = Vector3::Zero;
		offset.x += Math::RandomRange(-60.0f, 0.0f);
		offset.y += Math::RandomRange(-60.0f, 60.0f);
		transform->Move(offset);
	}

	/**************************************
	GaugeDebrisController�R���X�g���N�^
	***************************************/
	void GaugeDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::OutExpo);
		transform->SetScale(scale * Vector3::One);

		float currentSpeed = Easing::EaseValue(t, speed, 0.0f, EaseType::OutCubic);
		transform->Move(moveDir * currentSpeed);
	}

}

