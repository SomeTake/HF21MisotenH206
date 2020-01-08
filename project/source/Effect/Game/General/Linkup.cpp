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
		BaseParticleController(Particle_3D, false)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 Size = { 2.0f, 2.0f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, TexDiv);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/Linkup.png");

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxParticle = 128;
		const unsigned MaxEmitter = 16;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(3, 60);
			emitter->CreateParticleContainer<Linkup>(MaxParticle);
		}
	}

	/**************************************
	Linkup�R���X�g���N�^
	***************************************/
	Linkup::Linkup() :
		Particle3D(30, 45)
	{

	}

	/**************************************
	Linkup����������
	***************************************/
	void Linkup::Init()
	{
		cntFrame = 0;
		active = true;

		D3DXVECTOR3 offset = Vector3::Random() * Math::RandomRange(-8.0f, 8.0f);
		transform->Move(offset);

		initScale = Math::RandomRange(0.5f, 1.5f);

		uv.v = Math::RandomRange(0, 2) * 0.5f;
		uv.u = Math::RandomRange(0, 2) * 0.5f;
	}

	/**************************************
	Linkup�X�V����
	***************************************/
	void Linkup::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(Vector3::Up * 0.1f);

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);
	}

}