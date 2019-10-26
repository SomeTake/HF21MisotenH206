//=====================================
//
//WhiteSmog.cpp
//�@�\:���X���b�O
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "WhiteSmog.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	WhiteSmogController�R���X�g���N�^
	***************************************/
	WhiteSmogController::WhiteSmogController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 5.0f, 5.0f };
		const D3DXVECTOR2 DivineTex{ 8.0f, 8.0f };
		MakeUnitBuffer(SizeParticle, DivineTex);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/smog.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 512;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new WhiteSmog();
		}

		//�G�~�b�^�[�R���e�i�쐬����
		const unsigned MaxEmitter = 64;
		const int NumEmit = 8;
		const int DurationEmit = 3;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	WhiteSmog static�����o
	***************************************/
	const int WhiteSmog::MaxLife = 30;
	const int WhiteSmog::MinLife = 20;
	const float WhiteSmog::MaxSpeed = 2.5f;
	const float WhiteSmog::MinSpeed = 1.5f;

	/**************************************
	WhiteSmog�R���X�g���N�^
	***************************************/
	WhiteSmog::WhiteSmog() :
		AnimationParticle3D(8.0f, 8.0f, MinLife, MaxLife),
		directionMove(Vector3::Random()),
		speedMove(Math::RandomRange(MinSpeed, MaxSpeed))
	{
		directionMove.y = 0.0f;
		D3DXVec3Normalize(&directionMove, &directionMove);
	}

	/**************************************
	WhiteSmog����������
	***************************************/
	void WhiteSmog::Init()
	{
		cntFrame = 0;
		active = true;

		//�����_����Z����]
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//�ړ������ɏ������W���I�t�Z�b�g
		transform->Move(directionMove * 2.5f);
	}

	/**************************************
	WhiteSmog�X�V����
	***************************************/
	void WhiteSmog::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�o�ߎ��ԂŃA�j���[�V����
		float t = (float)cntFrame / lifeFrame;
		Animation(t);

		//�C�[�W���O�ňړ�
		float speed = Easing::EaseValue(t, speedMove, 0.0f, EaseType::OutCubic);
		transform->Move(speed * directionMove);
	}
}