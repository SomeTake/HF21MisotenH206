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
#include "../../Shader/RiverEffect.h"
#include "../../Field/Object/WaterHeightController.h"

//=====================================
// static�����o
//=====================================
const float RiverActor::FlowSpeed = 0.02f;

//=====================================
// �R���X�g���N�^
//=====================================
RiverActor::RiverActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel),
	direction(Forward),
	effect(nullptr)
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
	effect = new Field::Actor::RiverEffect();
}

//=====================================
// �f�X�g���N�^
//=====================================
RiverActor::~RiverActor()
{
	SAFE_DELETE(effect);
}

//=====================================
// �X�V����
//=====================================
void RiverActor::Update()
{
	PlaceActor::Update();

	D3DXVECTOR3 position = transform->GetPosition();
	position.y = WaterHeightController::GetHeight();
	transform->SetPosition(position);

	switch (direction)
	{
	case FlowDirection::Back:
		uv.y = Math::WrapAround(0.0f, 1.0f, uv.y - FlowSpeed);
		break;

	case FlowDirection::Forward:
		uv.y = Math::WrapAround(0.0f, 1.0f, uv.y + FlowSpeed);
		break;

	case FlowDirection::Right:
		uv.x = Math::WrapAround(0.0f, 1.0f, uv.x + FlowSpeed);
		break;

	case FlowDirection::Left:
		uv.x = Math::WrapAround(0.0f, 1.0f, uv.x - FlowSpeed);
		break;
	}

}

//=====================================
// �`�揈��
//=====================================
void RiverActor::Draw()
{
	if (!onCamera)
		return;

	effect->SetWorld(*transform);
	effect->SetUV(uv);
	
	effect->Begin();
	effect->BeginPass(0);

	mesh->Draw(*effect);

	effect->EndPass();
	effect->End();
}

//=====================================
// ���������̃Z�b�g����
//=====================================
void RiverActor::SetDirection(FlowDirection direction)
{
	this->direction = direction;
}
