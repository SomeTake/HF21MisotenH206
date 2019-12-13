//=====================================
//
// �V�e�B�A�N�^�[[CityActor.cpp]
// �@�\�F�s�s�i���A���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CityActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../Animation/ActorAnimation.h"
#include "../../Field/ActorLoader.h"
#include "../../../Framework/Renderer3D/MophingMeshContainer.h"

#define USE_MORPHING

//=====================================
// �R���X�g���N�^
//=====================================
CityActor::CityActor()
	: PlaceActor(),
	inMorphing(false),
	cntFrameMorphing(0)
{
	type = Field::Model::Town;
	morphContainer = new MorphingMeshContainer();
}

//=====================================
// �f�X�g���N�^
//=====================================
CityActor::~CityActor()
{
	SAFE_DELETE(morphContainer);
}

//=====================================
// ����������
//=====================================
void CityActor::Init(const D3DXVECTOR3 & pos, Field::FieldLevel currentLevel)
{
	using Field::Actor::ActorLoader;

#ifdef USE_MORPHING
	switch (currentLevel)
	{
	case Field::FieldLevel::City:
		for (int i = 0; i < 3; i++)
		{
			ResourceManager::Instance()->GetMesh(ActorLoader::CityTownTag[i].c_str(), morphContainer);
			morphContainer->RegisterVertex(i);
		}
		morphContainer->SetCurrent(0);
		morphContainer->SetNext(1);
		useMorphing = true;
		break;

	case Field::FieldLevel::World:
		for (int i = 0; i < 3; i++)
		{
			ResourceManager::Instance()->GetMesh(ActorLoader::WorldTownTag[i].c_str(), morphContainer);
			morphContainer->RegisterVertex(i);
		}
		morphContainer->SetCurrent(0);
		morphContainer->SetNext(1);
		useMorphing = true;
		break;

	case Field::FieldLevel::Space:
		ResourceManager::Instance()->GetMesh(ActorLoader::CityTag[currentLevel].c_str(), mesh);
		useMorphing = false;
		break;
	}
#else
	ResourceManager::Instance()->GetMesh(ActorLoader::CityTag[currentLevel].c_str(), mesh);
#endif

	PlaceActor::Init(pos, currentLevel);
}

//=====================================
// �I������
//=====================================
void CityActor::Uninit()
{
	morphContainer->ReleaseRegistration();
	PlaceActor::Uninit();
}

//=====================================
// �`�揈��
//=====================================
void CityActor::Draw()
{
	if (useMorphing)
	{
		cntFrameMorphing = Math::WrapAround(0, 60, ++cntFrameMorphing);

		float t = (float)cntFrameMorphing / 60;

		morphContainer->SetChange(t);
		morphContainer->Draw(transform->GetMatrix());
	}
	else
	{
		PlaceActor::Draw();
	}
}

//=====================================
// ���[�t�B���O�J�n
//=====================================
void CityActor::StartMorph(int next)
{
}
