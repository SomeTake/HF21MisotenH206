//=====================================
//
//���X�p�[�N�̔j�ЃG�t�F�N�g����[BlueDebris.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BlueDebris.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	BlueDebrisController�R���X�g���N�^
	***************************************/
	BlueDebrisController::BlueDebrisController()
	{
		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/blueDebris.png");

		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 ParticleSize{ 1.0f, 1.0f };
		const D3DXVECTOR2 TextureDiv{ (float)BlueDebris::TexDiv, (float)BlueDebris::TexDiv };
		MakeUnitBuffer(ParticleSize, TextureDiv);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new BlueDebris();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 4;
		const int DurationEmit = (int)(30 * 2.0f);
		const int NumEmit = 25;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	BlueDebris statci�����o
	***************************************/
	const int BlueDebris::MinLife = 10;
	const int BlueDebris::MaxLife = 20;
	const float BlueDebris::MinSpeed = 10.0f;
	const float BlueDebris::MaxSpeed = 3.0f;
	const int BlueDebris::TexDiv = 3;

	/**************************************
	BlueDebris�R���X�g���N�^
	***************************************/
	BlueDebris::BlueDebris() :
		Particle3D(MinLife, MaxLife),
		InitSpeed(Math::RandomRange(MinSpeed, MaxSpeed)),
		moveDirection(Vector3::Zero)
	{
	}

	/**************************************
	BlueDebris����������
	***************************************/
	void BlueDebris::Init()
	{
		cntFrame = 0;
		active = true;

		//�X�P�[�����O
		float scale = Math::RandomRange(0.2f, 1.2f);
		transform->SetScale(Vector3::One * scale);

		//�ړ�������ݒ�
		moveDirection = Vector3::Random();

		//UV���W������
		int indexUV = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = indexUV % TexDiv / (float)TexDiv;
		uv.v = indexUV / TexDiv / (float)TexDiv;

		//�����ʒu���ړ������փI�t�Z�b�g
		const float InitOffset = 10.0f;
		transform->Move(moveDirection * InitOffset);
	}

	/**************************************
	BlueDebris�X�V����
	***************************************/
	void BlueDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�X�s�[�h���C�[�W���O�ŋ��߂Ĉړ��v�Z
		float t = (float)cntFrame / lifeFrame;
		float speed = Easing::EaseValue(t, InitSpeed, 0.5f, EaseType::OutCirc);
		transform->Move(moveDirection * speed);

		//�X�P�[���v�Z
		float scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InCubic);
		transform->SetScale(Vector3::One * scale);

		//��]
		const float angleRotate = 10.0f;
		transform->Rotate(0.0f, 0.0f, angleRotate);
	}

}