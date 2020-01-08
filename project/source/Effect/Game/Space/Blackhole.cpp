//=====================================
//
//Blackhole.cpp
//�@�\:�u���b�N�z�[���p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "Blackhole.h"
#include "../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Camera/Camera.h"

namespace Effect::Game
{
	/**************************************
	static�����o
	***************************************/
	const float Blackhole::InitOffset = 6.0f;
	const float Blackhole::RangeHeight = 3.0f;

	/**************************************
	BlackholeController�R���X�g���N�^
	***************************************/	
	BlackholeController::BlackholeController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle = { 3.0f, 3.0f };
		MakeUnitBuffer(SizeParticle);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/blackhole.png");

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxParticle = 64;
		const unsigned MaxEmitter = 512;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BlackholeEmitter();
			emitter->CreateParticleContainer<Blackhole>(MaxParticle);
			emitter->UseCulling(true);
		}
	}

	/**************************************
	Blackhole�R���X�g���N�^
	***************************************/
	Blackhole::Blackhole() :
		Particle3D(15),
		position(Vector3::Zero)
	{

	}

	/**************************************
	Blackhole����������
	***************************************/
	void Blackhole::Init()
	{
		cntFrame = 0;
		active = true;

		position = transform->GetPosition();

		initAngle = Math::RandomRange(-D3DX_PI, D3DX_PI);

		height = Math::RandomRange(-RangeHeight, RangeHeight);

		initScale = Math::RandomRange(0.5f, 1.2f);
	}

	/**************************************
	Blackhole�X�V����
	***************************************/
	void Blackhole::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;
		float t = (float)cntFrame / lifeFrame;
		float angle = t * D3DX_PI * 0.5f;
		float length = Easing::EaseValue(t, InitOffset, InitOffset * 0.1f, EaseType::InOutCubic);
		
		D3DXVECTOR3 currentPosition = position + D3DXVECTOR3(cosf(angle + initAngle), 0.0f, sinf(angle + initAngle)) * length;
		currentPosition.y = position.y + Easing::EaseValue(t, height, 0.0f, EaseType::InOutCubic);
		transform->SetPosition(currentPosition);

		float scale = Easing::EaseValue(t, initScale, initScale * 0.1f, EaseType::InOutCubic);
		transform->SetScale(Vector3::One * scale);
	}

	/**************************************
	BlackholeEmitter�R���X�g���N�^
	***************************************/
	BlackholeEmitter::BlackholeEmitter() :
		BaseEmitter(5)
	{
		flgLoop = true;
	}

	/**************************************
	BlackholeEmitter�A�N�e�B�u����
	***************************************/
	bool BlackholeEmitter::IsActive() const
	{
		return active;
	}

}