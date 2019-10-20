//=====================================
//
//���X�p�[�N����[BlueSpark.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BlueSpark.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	BlueSparkController�R���X�g���N�^
	***************************************/
	BlueSparkController::BlueSparkController()
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 ParticleSize{ 25.0f, 15.0f };
		MakeUnitBuffer(ParticleSize);

		//�e�N�X�`���ǂݍ���
		const char* path = "data/TEXTURE/Particle/blueSpark.png";
		LoadTexture(path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new BlueSpark();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 4;
		const int NumEmit = 5;
		const int DurationEmit = 30 * 4;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	BlueSpark static�����o
	***************************************/
	const int BlueSpark::MaxLife = 15;
	const int BlueSpark::MinLife = 5;

	/**************************************
	BlueSpark�R���X�g���N�^
	***************************************/
	BlueSpark::BlueSpark() :
		BaseParticle(MinLife, MaxLife),
		angleRotate(Math::RandomRange(0.0f, 360.0f))
	{

	}

	/**************************************
	BlueSpark����������
	***************************************/
	void BlueSpark::Init()
	{
		cntFrame = 0;
		active = true;

		//��]
		transform->Rotate(angleRotate, Vector3::Back);

		//�ړ�
		float posY = Math::RandomRange(-5.0f, 5.0f);
		transform->Move(Vector3::Up * posY);
		//�X�P�[�����O
		initScaleX = Math::RandomRange(1.0f, 3.0f);
		transform->SetScale({ initScaleX, 1.0f, 1.0f });
	}

	/**************************************
	BlueSpark�X�V����
	***************************************/
	void BlueSpark::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float scaleY = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InCubic);
		transform->SetScale({ initScaleX, scaleY, 1.0f });
	}
}