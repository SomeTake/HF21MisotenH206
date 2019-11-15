//=====================================
//
//StarRoad.cpp
//�@�\:���̓��p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "StarRoad.h"

namespace Effect::Game
{
	/**************************************	
	StarRoadController�R���X�g���N�^
	***************************************/
	StarRoadController::StarRoadController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle = { 3.0f, 3.0f };
		MakeUnitBuffer(SizeParticle);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/star.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 1024; 
		particleContainer.resize(MaxParticle);
		for (auto&& particle : particleContainer)
		{
			particle = new StarRoad();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 32;
		emitterContainer.resize(MaxEmitter);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new StarRoadEmitter();
		}
	}

	/**************************************
	StarRoad�R���X�g���N�^
	***************************************/
	StarRoad::StarRoad() :
		Particle3D(15)
	{

	}

	/**************************************
	StarRoad����������
	***************************************/
	void StarRoad::Init()
	{
		const float RangeXZ = 2.0f;
		const float RangeY = 1.0f;

		D3DXVECTOR3 offset = {
			Math::RandomRange(-RangeXZ, RangeXZ),
			Math::RandomRange(-RangeY, RangeY),
			Math::RandomRange(-RangeXZ, RangeXZ)
		};

		transform->Move(offset);

		cntFrame = 0;
		active = true;
	}

	/**************************************
	StarRoad�X�V����
	***************************************/
	void StarRoad::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		uv.u += 0.02f;
		uv.v -= 0.02f;
	}

	/**************************************
	StarRoadEmitter�R���X�g���N�^
	***************************************/
	StarRoadEmitter::StarRoadEmitter() :
		BaseEmitter(2)
	{
	}

	/**************************************
	StarRoadEmitter�A�N�e�B�u����
	***************************************/
	bool StarRoadEmitter::IsActive() const
	{
		//��x�Z�b�g���ꂽ�疳���ɕ��o��������
		return active;
	}

}