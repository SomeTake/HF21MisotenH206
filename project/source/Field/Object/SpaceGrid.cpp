//=====================================
//
//SpaceGrid.cpp
//�@�\:�F�����x���̃O���b�h
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SpaceGrid.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"

/**************************************
�R���X�g���N�^
***************************************/
SpaceGrid::SpaceGrid()
{
	polygon = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("SpaceGrid", polygon);

	polygon->SetTexDiv({ 0.02f, 0.02f });

	const D3DXVECTOR3 position = D3DXVECTOR3(250.0f, 0.0f, -250.0f) - D3DXVECTOR3(5.0f, 0.0f, 5.0f);
	transform->SetPosition(position);
	transform->Rotate(90.0f, Vector3::Right);
}

/**************************************
�f�X�g���N�^
***************************************/
SpaceGrid::~SpaceGrid()
{
	SAFE_DELETE(polygon);
}

void SpaceGrid::Update()
{
	cntFrame = Math::WrapAround(0, 90, ++cntFrame);
	float alpha = cntFrame / 90.0f * 1.0f;
	polygon->SetDiffuse(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
}

/**************************************
�`�揈��
***************************************/
void SpaceGrid::Draw()
{

	polygon->Draw(transform->GetMatrix());
}
