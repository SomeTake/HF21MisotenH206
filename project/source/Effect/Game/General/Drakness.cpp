//=============================================================================
//
// AI���x�������G�t�F�N�g�N���X [Darkness.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "Darkness.h"
#include "../../../../Framework/Math/Easing.h"

// �����o����p�[�e�B�N���̐�
static const int OnceParticleNum = 4;

namespace Effect::Game
{
	/**************************************
	DarknessController�R���X�g���N�^
	***************************************/
	DarknessController::DarknessController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 2.0f, 2.0f };
		const D3DXVECTOR2 DivineTex{ 2.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/DarknessDebris.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto &particle : particleContainer)
		{
			particle = new Darkness();
		}

		//�G�~�b�^�[�R���e�i�쐬����
		const unsigned MaxEmitter = 1;
		const int NumEmit = 8;
		const int DurationEmit = 90;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	Darkness static�����o
	***************************************/
	const int Darkness::MinLife = 30;
	const int Darkness::MaxLife = 50;
	const float Darkness::MinSpeed = 0.7f;
	const float Darkness::MaxSpeed = 0.3f;
	const int Darkness::TexDiv = 2;

	/**************************************
	Darkness�R���X�g���N�^
	***************************************/
	Darkness::Darkness() :
		Particle3D(MinLife, MaxLife),
		Speed(Math::RandomRange(MinSpeed, MaxSpeed))
	{
	}

	/**************************************
	Darkness����������
	***************************************/
	void Darkness::Init()
	{
		static int ParticleCount = 0;

		cntFrame = 0;
		active = true;
		ParticleCount++;
		ParticleCount %= 36;

		//UV���W������
		int indexUV = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = indexUV % TexDiv / (float)TexDiv;
		uv.v = indexUV / TexDiv / (float)TexDiv;

		//�����ʒu���ړ������փI�t�Z�b�g
		float BaseAngle = 360.0f / 36;
		//float Theta = Math::RandomRange(0, 36) * BaseAngle;
		float Theta = ParticleCount * BaseAngle;
		D3DXVECTOR3 InitOffset = D3DXVECTOR3
		(
			7.0f * cosf(D3DXToRadian(Theta)),
			Math::RandomRange(15.0f, 20.0f),
			//20.0f,
			7.0f * sinf(D3DXToRadian(Theta))
		);
		transform->Move(InitOffset);
	}

	/**************************************
	Darkness�X�V����
	***************************************/
	void Darkness::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(Vector3::Down * Speed);
		if (transform->GetPosition().y <= 0.0f)
		{
			SetActive(false);
		}
	}
}