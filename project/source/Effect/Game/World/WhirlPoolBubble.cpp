//=====================================
//
//WhirlPoolBubble.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "WhirlPoolBubble.h"
#include "../../../../Framework/Camera/Camera.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	static�����o
	***************************************/
	const float WhirlPoolBubble::LengthPopup = 1.0f;
	const float WhirlPoolBubble::LengthOffset = 5.0f;

	/**************************************
	WhirlPoolController�R���X�g���N�^
	***************************************/
	WhirlPoolController::WhirlPoolController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle = { 1.5f, 1.5f };
		MakeUnitBuffer(SizeParticle);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/WhirlPoolBubble.png");

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxParticle = 64;
		const unsigned MaxEmitter = 512;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new WhirlPoolBubbleEmitter();
			emitter->CreateParticleContainer<WhirlPoolBubble>(MaxParticle);
			emitter->UseCulling(true);
		}
	}

	/**************************************
	WhirlPoolBubble�R���X�g���N�^
	***************************************/
	WhirlPoolBubble::WhirlPoolBubble() :
		Particle3D(20),
		position(Vector3::Zero)
	{

	}

	/**************************************
	WhirlPoolBubble����������
	***************************************/
	void WhirlPoolBubble::Init()
	{
		cntFrame = 0;
		active = true;

		position = transform->GetPosition();

		initOffset = Math::RandomRange(-D3DX_PI, D3DX_PI);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);
	}

	/**************************************
	WhirlPoolBubble�X�V����
	***************************************/
	void WhirlPoolBubble::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;
		float t = (float)cntFrame / lifeFrame * D3DX_PI * 0.2f;
		float popup = sinf(t * 10.0f) * LengthPopup;

		D3DXVECTOR3 currentPosition = position + D3DXVECTOR3(cosf(t + initOffset) * LengthOffset, popup, sinf(t + initOffset) * LengthOffset);
		transform->SetPosition(currentPosition);
	}

	/**************************************
	WhirlPoolBubbleEmiter�R���X�g���N�^
	***************************************/
	WhirlPoolBubbleEmitter::WhirlPoolBubbleEmitter() :
		BaseEmitter(3)
	{
		flgLoop = true;
	}
}