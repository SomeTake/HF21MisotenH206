//=====================================
//
//StarRoad.cpp
//�@�\:���̓��p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "StarRoad.h"
#include "../../../Framework/Camera/Camera.h"

namespace Effect::Game
{
	/**************************************
	StarRoad static�����o
	***************************************/
	const float StarRoad::RangeX = 2.0f;
	const float StarRoad::RangeY = 1.0f;
	const float StarRoad::MaxRangeZ = 8.0f;
	const float StarRoad::MinRangeZ = -2.0f;

	/**************************************	
	StarRoadController�R���X�g���N�^
	***************************************/
	StarRoadController::StarRoadController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle = { 6.0f, 6.0f };
		const D3DXVECTOR2 TexDiv = { 2.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, TexDiv);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/star.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 2048; 
		particleContainer.resize(MaxParticle);
		for (auto&& particle : particleContainer)
		{
			particle = new StarRoad();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 1024;
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
		Particle3D(15),
		direction(transform->Forward())
	{

	}

	/**************************************
	StarRoad����������
	***************************************/
	void StarRoad::Init()
	{
		D3DXVECTOR3 offset = Vector3::Zero;
		offset += transform->Right() * Math::RandomRange(-RangeX, RangeX);
		offset += transform->Up() * Math::RandomRange(-RangeY, RangeY);
		offset += transform->Forward() * Math::RandomRange(MinRangeZ, MaxRangeZ);

		transform->Move(offset);

		transform->SetRotation(Vector3::Zero);

		uv.u = Math::RandomRange(0, 2) * 0.5f;
		uv.v = Math::RandomRange(0, 2) * 0.5f;


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

		transform->Move(direction * 0.2f);
	}

	/**************************************
	StarRoad�ړ������ݒ菈��
	***************************************/
	void StarRoad::Toward(const D3DXVECTOR3 & direction)
	{
		this->direction = direction;
	}

	/**************************************
	StarRoadEmitter�R���X�g���N�^
	***************************************/
	StarRoadEmitter::StarRoadEmitter() :
		BaseEmitter(3)
	{
	}

	/**************************************
	StarRoadEmitter���o����
	***************************************/
	bool StarRoadEmitter::Emit(std::vector<BaseParticle*>& container)
	{
		if (!IsActive())
			return true;

		//�`��̈�O����������o���Ȃ�
		D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());
		if (screenPos.x < 0.0f || screenPos.x >(float)SCREEN_WIDTH * 1.2f || screenPos.y < 0.0f || screenPos.y >(float)SCREEN_HEIGHT * 1.2f)
			return true;

		UINT cntEmit = 0;
		for (auto& particle : container)
		{
			if (particle->IsActive())
				continue;

			//����������
			particle->SetTransform(*transform);
			dynamic_cast<StarRoad*>(particle)->Toward(transform->Forward());
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
	StarRoadEmitter�A�N�e�B�u����
	***************************************/
	bool StarRoadEmitter::IsActive() const
	{
		//��x�Z�b�g���ꂽ�疳���ɕ��o��������
		return active;
	}

}