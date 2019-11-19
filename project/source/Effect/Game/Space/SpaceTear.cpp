//=====================================
//
//SpaceTear.cpp
//�@�\:����f��p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SpaceTear.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	SpaceTearController�R���X�g���N�^
	***************************************/
	SpaceTearController::SpaceTearController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle = { 20.0f, 20.0f };
		const D3DXVECTOR2 TextureDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, TextureDiv);

		//�e�N�X�`���ǂݍ���
		const char* TexturePath = "data/TEXTURE/Particle/TearSpark.png";
		LoadTexture(TexturePath);

		//�p�[�e�B�N���R���e�i�쐬
		const size_t MaxParticle = 2048;
		particleContainer.resize(MaxParticle);
		for (auto&& particle : particleContainer)
		{
			particle = new SpaceTear();
		}

		//�G�~�b�^�R���e�i�쐬
		const size_t MaxEmitter = 512;
		emitterContainer.resize(MaxEmitter);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new SpaceTearEmitter();
		}
	}

	/**************************************
	SpaceTear static�����o
	***************************************/
	const int SpaceTear::MaxLife = 5;
	const int SpaceTear::MinLife = 3;

	/**************************************
	SpaceTear�R���X�g���N�^
	***************************************/
	SpaceTear::SpaceTear() :
		Particle3D(MinLife, MaxLife),
		angleRotate(Math::RandomRange(-20.0f, 20.0f))
	{
		//�e�N�X�`���̒ʂ��ԍ��������_���Ɍ���
		int indexU = Math::RandomRange(0, 2);
		int indexV = Math::RandomRange(0, 2);

		uv.u = indexU * 0.5f;
		uv.v = indexV * 0.5f;
	}

	/**************************************
	SpaceTear����������
	***************************************/
	void SpaceTear::Init()
	{
		cntFrame = 0;
		active = true;

		//��]
		transform->Rotate(angleRotate, Vector3::Forward);

		//�ړ�
		float posY = Math::RandomRange(-1.0f, 1.0f);
		transform->Move(Vector3::Up * posY);

		//�X�P�[�����O
		initScaleX = Math::RandomRange(0.5f, 2.0f);
		initScaleY = Math::RandomRange(0.5f, 1.5f);
		transform->SetScale({ initScaleX, initScaleY, 1.0f });
	}

	/**************************************
	SpaceTear�X�V����
	***************************************/
	void SpaceTear::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;
		float scaleY = Easing::EaseValue(t, initScaleY, 0.0f, EaseType::InCubic);
		transform->SetScale({ initScaleX, scaleY, 1.0 });
	}

	/**************************************
	SpaceTearEmitter�R���X�g���N�^
	***************************************/
	SpaceTearEmitter::SpaceTearEmitter() :
		BaseEmitter(1, 0)
	{

	}

	/**************************************
	SpaceTearEmitter�A�N�e�B�u����
	***************************************/
	bool SpaceTearEmitter::IsActive() const
	{
		if (!active)
			return false;

		return true;

		//�V�[���I���܂ŕ��o�����������������̂�
		//�J�E���g�ł̃A�N�e�B�u����͍s��Ȃ�
	}

}