//=====================================
//
//AngryFace.cpp
//�@�\:�{���2D�p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "AngryFace.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	AngryFaceController::AngryFaceController() :
		BaseParticleController(Particle_2D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		//�X�N���[�����W�ň����̂�Y�T�C�Y���}�C�i�X�ɂ��邱�Ƃɒ���
		const D3DXVECTOR2 SizeParticle{ 100.0f, -100.0f };
		MakeUnitBuffer(SizeParticle);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/angryFace.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const int MaxParticle = 1024;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new AngryFace();
		}

		//�G�~�b�^�R���e�i�쐬
		const int MaxEmitter = 4;
		const int DurationEmit = 60;
		const int NumEmit = 15;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	AngryFace�R���X�g���N�^
	***************************************/
	const int AngryFace::Life = 45;

	/**************************************
	AngryFace�R���X�g���N�^
	***************************************/
	AngryFace::AngryFace() :
		Particle2D(Life),
		targetScale(1.0f)
	{

	}

	/**************************************
	AngryFace�f�X�g���N�^
	***************************************/
	AngryFace::~AngryFace()
	{
	}

	/**************************************
	AngryFace����������
	***************************************/
	void AngryFace::Init()
	{
		targetScale = Math::RandomRange(0.8f, 2.0f);
		cntFrame = 0;
		active = true;

		D3DXVECTOR3 position{
			(float)Math::RandomRange(0, SCREEN_WIDTH),
			(float)Math::RandomRange(0, SCREEN_HEIGHT),
			0.0f
		};
		transform->SetPosition(position);
	}

	/**************************************
	AngryFace�X�V����
	***************************************/
	void AngryFace::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame * 2.0f;

		float scale = Easing::EaseValue(t, 0.0f, targetScale, EaseType::InExpo);
		transform->SetScale(scale * Vector3::One);
	}
}