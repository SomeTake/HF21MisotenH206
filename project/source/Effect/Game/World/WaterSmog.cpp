//=============================================================================
//
// ���̖��G�t�F�N�g�N���X [WaterSmog.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "WaterSmog.h"
#include "../../../../Framework/Math/Easing.h"



namespace Effect::Game
{
	/**************************************
	WaterSmogController static�����o
	***************************************/
	int WaterSmogController::FrameCount = 0;

	/**************************************
	WaterSmogController�R���X�g���N�^
	***************************************/
	WaterSmogController::WaterSmogController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 5.0f, 5.0f };
		const D3DXVECTOR2 DivineTex{ 8.0f, 8.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/WaterSmog.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new WaterSmog();
		}

		//�G�~�b�^�[�R���e�i�쐬����
		const unsigned MaxEmitter = 1;
		const int NumEmit = 8;
		const int DurationEmit = 60;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	WaterSmogController�X�V����
	***************************************/
	void WaterSmogController::Update(void)
	{
		if (emitterContainer.at(0)->IsActive())
		{
			FrameCount++;
			FrameCount %= 60;
		}
		else
		{
			FrameCount = 0;
		}

		BaseParticleController::Update();
	}

	/**************************************
	WaterSmog static�����o
	***************************************/
	const int WaterSmog::MaxLife = 30;
	const int WaterSmog::MinLife = 10;

	/**************************************
	WaterSmog�R���X�g���N�^
	***************************************/
	WaterSmog::WaterSmog() :
		AnimationParticle3D(8.0f, 8.0f, MinLife, MaxLife)
	{
	}

	/**************************************
	WaterSmog����������
	***************************************/
	void WaterSmog::Init()
	{
		cntFrame = 0;
		active = true;

		//�����_����Z����]
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//�����ʒu���ړ������փI�t�Z�b�g
		float BaseAngle = 10.0f;
		float Theta = Math::RandomRange(0, 36) * BaseAngle;
		float T = (float)WaterSmogController::FrameCount / 60.0f;
		float Length_Max = Easing::EaseValue(T, 5.0f, 15.0f, EaseType::Linear);
		float Length = Math::RandomRange(0.0f, Length_Max);
		D3DXVECTOR3 InitOffset = D3DXVECTOR3
		(
			Length * cosf(D3DXToRadian(Theta)),
			Math::RandomRange(1.0f, 1.5f),
			Length * sinf(D3DXToRadian(Theta))
		);
		transform->Move(InitOffset);

		//�X�P�[���������_���ɕύX
		float scale = Math::RandomRange(0.5f, 1.0f);
		transform->SetScale(scale * Vector3::One);
	}

	/**************************************
	WaterSmog�X�V����
	***************************************/
	void WaterSmog::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�o�ߎ��ԂŃA�j���[�V����
		float t = (float)cntFrame / lifeFrame;
		Animation(t);

		//�C�[�W���O�ňړ�
		//float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::OutCubic);
		//transform->Move(speed * directionMove);
	}
}