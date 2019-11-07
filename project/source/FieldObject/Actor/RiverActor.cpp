//=====================================
//
// ���o�[�A�N�^�[[RiverActor.cpp]
// �@�\�F��i����f��j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "RiverActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Math/Easing.h"

//=====================================
// static�����o
//=====================================
const int RiverActor::AnimationPeriod = 360;
const float RiverActor::MaxWaveHeight = 0.015f;
float RiverActor::heightWave = 0.0f;
int RiverActor::cntWaveAnimation = 0;

//=====================================
// �R���X�g���N�^
//=====================================
RiverActor::RiverActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel),
	direction(Forward)
{
	// ���f���f�[�^�Q��
	switch (currentLevel)
	{
	case Field::City:
		ResourceManager::Instance()->GetMesh("River-City", mesh);
		break;
	case Field::World:
		break;
	case Field::Space:
		ResourceManager::Instance()->GetMesh("River-Space", mesh);
		break;
	default:
		break;
	}

	type = Field::Model::River;
}

//=====================================
// �f�X�g���N�^
//=====================================
RiverActor::~RiverActor()
{
}

//=====================================
// �X�V����
//=====================================
void RiverActor::Update()
{
	PlaceActor::Update();

	transform->Move(Vector3::Up * heightWave);
}

//=====================================
// ���������̃Z�b�g����
//=====================================
void RiverActor::SetDirection(FlowDirection direction)
{
	this->direction = direction;
}

//=====================================
// �����̍X�V����
//=====================================
void RiverActor::UpdateHeight()
{
	cntWaveAnimation = Math::WrapAround(0, AnimationPeriod, ++cntWaveAnimation);

	float startHeight = (cntWaveAnimation < AnimationPeriod / 2) ? -MaxWaveHeight : MaxWaveHeight;
	float goalHeight = startHeight * -1.0f;
	float t = (cntWaveAnimation < AnimationPeriod / 2) ? cntWaveAnimation / (AnimationPeriod * 0.5f) : (cntWaveAnimation - AnimationPeriod * 0.5f) / (AnimationPeriod * 0.5f);

	heightWave = Easing::EaseValue(t, startHeight, goalHeight, EaseType::InOutBack);
}
