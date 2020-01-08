//=============================================================================
//
// �X�^�[�_�X�g�G�t�F�N�g�N���X [StarDust.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "StarDust.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	StarDustController�R���X�g���N�^
	***************************************/
	StarDustController::StarDustController() :
		BaseParticleController(Particle_3D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle{ 2.0f, 2.0f };
		const D3DXVECTOR2 TextureDivine{ (float)StarDust::TexDiv, (float)StarDust::TexDiv };
		MakeUnitBuffer(SizeParticle, TextureDivine);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/levelup.png";
		LoadTexture(Path);

		//�G�~�b�^�R���e�i�쐬
		const unsigned MaxParticle = 256;
		const unsigned MaxEmitter = 1;
		const int DurationEmit = 60;
		const int NumEmit = 8;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
			emitter->CreateParticleContainer<StarDust>(MaxParticle);
		}
	}

	/**************************************
	�`��
	***************************************/
	bool StarDustController::Draw(void)
	{
		bool Result = false;
		LPDIRECT3DDEVICE9 Device = GetDevice();

		//�����_�[�X�e�[�g�����Z�����ɐݒ�
		//Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		Result = BaseParticleController::Draw();

		//�����_�[�X�e�[�g�����ɖ߂�
		//Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		return Result;
	}

	/**************************************
	Emitter�̈ʒu��ݒ�
	***************************************/
	void StarDustController::SetEmitterPos(D3DXVECTOR3 Pos)
	{
		for (auto&& emitter : emitterContainer)
		{
			if (emitter->IsActive())
				emitter->SetPosition(Pos);
		}
	}

	/**************************************
	StarDust static�����o
	***************************************/
	const int StarDust::MinLife = 10;
	const int StarDust::MaxLife = 15;
	const float StarDust::MinScale = 0.5;
	const float StarDust::MaxScale = 1.0f;
	const int StarDust::TexDiv = 6;

	/**************************************
	StarDust�R���X�g���N�^
	***************************************/
	StarDust::StarDust() :
		Particle3D(MinLife, MaxLife),
		initScale(Math::RandomRange(MinScale, MaxScale)),
		directionMove(Vector3::Random())
	{
		//directionMove.y = Math::RandomRange(0.0f, 0.5f);
		//D3DXVec3Normalize(&directionMove, &directionMove);
	}

	/**************************************
	StarDust����������
	***************************************/
	void StarDust::Init()
	{
		int randomIndex = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = randomIndex % TexDiv * 1.0f / TexDiv;
		uv.v = randomIndex / TexDiv * 1.0f / TexDiv;

		cntFrame = 0;
		active = true;

		//�����_����Z����]
		transform->SetRotation(Vector3::Forward * Math::RandomRange(0.0f, 360.0f));

		//�ړ������ɏ������W���I�t�Z�b�g
		D3DXVECTOR3 InitOffset = D3DXVECTOR3
		(
			Math::RandomRange(-1.0f, 1.0f),
			Math::RandomRange(-1.0f, 1.0f),
			Math::RandomRange(-1.0f, 1.0f)
		) * 7.0f;
		transform->Move(InitOffset);
	}

	/**************************************
	StarDust�X�V����
	***************************************/
	void StarDust::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		const float EndScale = 0.0f;
		float scale = Easing::EaseValue(t, initScale, EndScale, EaseType::InQuint);
		transform->SetScale(Vector3::One * scale);

		const float angleRotate = 33.0f;
		//transform->Rotate(0.0f, 0.0f, angleRotate);
	}

}