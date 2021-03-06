//=====================================
//
//Cloud.cpp
//機能:雲パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Cloud.h"
#include "../../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	staticメンバ
	***************************************/
	const float Cloud::MinSpeed = 10.0f;
	const float Cloud::MaxSpeed = 40.0f;
	const float Cloud::MinPositionX = -300.0f;
	const float Cloud::MaxPositionX = SCREEN_WIDTH + 300.0f;
	const float Cloud::MinPositionY = -300.0f;
	const float Cloud::MaxPositionY = SCREEN_HEIGHT + 300.0f;

	/**************************************
	コンストラクタ
	***************************************/
	CloudController::CloudController() :
		BaseParticleController(Particle_2D, false)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 250.0f, -250.0f };
		const D3DXVECTOR2 DivParticle = { 3.0f, 2.0f };
		MakeUnitBuffer(SizeParticle, DivParticle);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/cloud.png");

		//エミッタコンテナ作成
		const unsigned MaxEmitter = 1;
		const unsigned MaxParticle = 1024;
		emitterContainer.resize(MaxEmitter);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new CloudEmitter();
			emitter->CreateParticleContainer<Cloud>(MaxParticle);
		}
	}

	/**************************************
	Cloudコンストラクタ
	***************************************/
	Cloud::Cloud() :
		Particle2D(60)
	{

	}

	/**************************************
	Cloud初期化処理
	***************************************/
	void Cloud::Init()
	{
		float u = Math::RandomRange(0, 3) / 3.0f;
		float v = Math::RandomRange(0, 2) / 2.0f;
		uv = ParticleUV(u, v);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

		initScale = Math::RandomRange(0.8f, 2.5f);
		transform->SetScale(Vector3::One * initScale);

		cntFrame = 0;
		active = true;
	}

	/**************************************
	Cloud更新処理
	***************************************/
	void Cloud::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		transform->Move(velocity);

		transform->Rotate(0.5f, Vector3::Forward);

		float t = (float)cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);
	}

	/**************************************
	Cloud方向設定処理
	***************************************/
	void Cloud::SetDirection(bool isDown)
	{
		if (isDown)
		{
			D3DXVECTOR3 position = Vector3::Zero;
			position.x = Math::RandomRange(MinPositionX, MaxPositionX);
			position.y = MinPositionY;
			transform->SetPosition(position);

			velocity = Vector3::Normalize({ -1.0f, 1.0f, 0.0f }) * Math::RandomRange(MinSpeed, MaxSpeed);
		}
		else
		{
			D3DXVECTOR3 position = Vector3::Zero;
			position.x = Math::RandomRange(MinPositionX, MaxPositionX);
			position.y = MaxPositionY;
			transform->SetPosition(position);

			velocity = Vector3::Normalize({ 1.0f, -1.0f, 0.0f }) * Math::RandomRange(MinSpeed, MaxSpeed);
		}
	}

	/**************************************
	CloudEmitterコンストラクタ
	***************************************/
	CloudEmitter::CloudEmitter() :
		BaseEmitter(15, 30)
	{

	}

	/**************************************
	CloudEmitter放出処理
	***************************************/
	bool CloudEmitter::Emit()
	{
		if (!enableEmit)
			return true;

		int cntEmit = 0;
		for (auto&& particle : particleContainer)
		{
			if (particle->IsActive())
				continue;

			//初期化処理
			Cloud* entity = dynamic_cast<Cloud*>(particle);
			entity->SetDirection(cntEmit < emitNum / 2);
			entity->Init();

			cntEmit++;

			if (cntEmit == emitNum)
				return true;
		}

		return false;
	}
}

