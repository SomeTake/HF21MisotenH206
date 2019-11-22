//=====================================
//
//Cloud.cpp
//�@�\:�_�p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "Cloud.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	static�����o
	***************************************/
	const float Cloud::MinSpeed = 10.0f;
	const float Cloud::MaxSpeed = 40.0f;
	const float Cloud::MinPositionX = -100.0f;
	const float Cloud::MaxPositionX = SCREEN_WIDTH + 100.0f;
	const float Cloud::MinPositionY = -100.0f;
	const float Cloud::MaxPositionY = SCREEN_HEIGHT + 100.0f;

	/**************************************
	�R���X�g���N�^
	***************************************/
	CloudController::CloudController() :
		BaseParticleController(Particle_2D, false)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle = { 200.0f, -200.0f };
		const D3DXVECTOR2 DivParticle = { 3.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivParticle);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/cloud.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 1024;
		particleContainer.resize(MaxParticle);
		for (auto&& particle : particleContainer)
		{
			particle = new Cloud();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 4;
		emitterContainer.resize(MaxEmitter);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new CloudEmitter();
		}
	}

	/**************************************
	Cloud�R���X�g���N�^
	***************************************/
	Cloud::Cloud() :
		Particle2D(60)
	{

	}

	/**************************************
	Cloud����������
	***************************************/
	void Cloud::Init()
	{
		float u = Math::RandomRange(0, 3) / 3.0f;
		float v = Math::RandomRange(0, 2) / 2.0f;
		uv = ParticleUV(u, v);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

		initScale = Math::RandomRange(0.8f, 2.0f);
		transform->SetScale(Vector3::One * initScale);

		cntFrame = 0;
		active = true;
	}

	/**************************************
	Cloud�X�V����
	***************************************/
	void Cloud::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(velocity);

		transform->Rotate(0.5f, Vector3::Forward);

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);
	}

	/**************************************
	Cloud�����ݒ菈��
	***************************************/
	void Cloud::SetDirection(bool isDown)
	{
		if (isDown)
		{
			D3DXVECTOR3 position = Vector3::Zero;
			position.x = Math::RandomRange(MinPositionX, MaxPositionX);
			position.y = MinPositionY;
			transform->SetPosition(position);

			velocity = Vector3::Normalize({ -1.0f, 1.0f, 0.0f }) * Math::RandomRange(MinSpeed, MaxSpeed);
		}
		else
		{
			D3DXVECTOR3 position = Vector3::Zero;
			position.x = Math::RandomRange(MinPositionX, MaxPositionX);
			position.y = MaxPositionY;
			transform->SetPosition(position);

			velocity = Vector3::Normalize({ 1.0f, -1.0f, 0.0f }) * Math::RandomRange(MinSpeed, MaxSpeed);
		}
	}

	/**************************************
	CloudEmitter�R���X�g���N�^
	***************************************/
	CloudEmitter::CloudEmitter() :
		BaseEmitter(14, 30)
	{

	}

	/**************************************
	CloudEmitter���o����
	***************************************/
	bool CloudEmitter::Emit(std::vector<BaseParticle*>& container)
	{
		if (!IsActive())
			return true;

		int cntEmit = 0;
		for (auto&& particle : container)
		{
			if (particle->IsActive())
				continue;

			//����������
			Cloud* entity = dynamic_cast<Cloud*>(particle);
			entity->SetDirection(cntEmit < emitNum / 2);
			entity->Init();

			cntEmit++;

			if (cntEmit == emitNum)
				return true;
		}

		return false;
	}
}

