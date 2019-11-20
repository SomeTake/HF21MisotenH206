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

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 4096;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new WhirlPoolBubble();
		}

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxEmitter = 512;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new WhirlPoolBubbleEmitter();
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
	}

	/**************************************
	WhirlPoolBubbleEmitter���o����
	***************************************/
	bool WhirlPoolBubbleEmitter::Emit(std::vector<BaseParticle*>& container)
	{
		if (!IsActive())
			return true;

		//�`��̈�O����������o���Ȃ�
		D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());
		if (screenPos.x < 0.0f || screenPos.x >(float)SCREEN_WIDTH || screenPos.y < 0.0f || screenPos.y >(float)SCREEN_HEIGHT)
			return true;

		UINT cntEmit = 0;
		for (auto& particle : container)
		{
			if (particle->IsActive())
				continue;

			//����������
			particle->SetTransform(*transform);
			particle->Init();

			//�J�E���g
			cntEmit++;

			//���߂�ꐔ�������o���Ă�����I��
			if (cntEmit == emitNum)
				return true;
		}

		return false;
	}

	/**************************************
	WhirlPoolBubbleEmitter�A�N�e�B�u����
	***************************************/
	bool WhirlPoolBubbleEmitter::IsActive() const
	{
		//��x�Z�b�g���ꂽ�疳���ɕ��o��������
		return active;
	}

}