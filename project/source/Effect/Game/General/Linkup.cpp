//=====================================
//
//�����N�A�b�v�G�t�F�N�g����[Linkup.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Linkup.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	LinkupController�R���X�g���N�^
	***************************************/
	LinkupController::LinkupController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 1.0f, 1.0f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, TexDiv);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/Linkup.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new Linkup();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 16;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(5, 60);
		}
	}

	/**************************************
	Linkup�R���X�g���N�^
	***************************************/
	Linkup::Linkup() :
		Particle3D(15, 30)
	{

	}

	/**************************************
	Linkup����������
	***************************************/
	void Linkup::Init()
	{
		cntFrame = 0;
		active = true;

		D3DXVECTOR3 offset = Vector3::Random() * Math::RandomRange(-2.0f, 2.0f);
		transform->Move(offset);

		initScale = Math::RandomRange(0.5f, 1.5f);
	}

	/**************************************
	Linkup�X�V����
	***************************************/
	void Linkup::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(Vector3::Up * 0.05f);

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::OutCubic);
		transform->SetScale(Vector3::One * scale);
	}

}