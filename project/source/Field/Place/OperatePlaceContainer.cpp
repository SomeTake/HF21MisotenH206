//=====================================
//
//OperatePlaceContainer.cpp
//�@�\:����Ώۂ̃v���C�X���i�[����R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "OperatePlaceContainer.h"
#include "FieldPlaceModel.h"

#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Tween/Tween.h"

#include "../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using�錾
	***************************************/
	using cpplinq::from;
	using cpplinq::where;
	using cpplinq::count;

	/**************************************
	�R���X�g���N�^
	***************************************/
	OperatePlaceContainer::OperatePlaceContainer()
	{
		const D3DXVECTOR2 SizePin{ 4.5f, 4.5f };
		ResourceManager::Instance()->MakePolygon("PinActor", "data/TEXTURE/Field/fieldpin.png", SizePin, { 2.0f, 1.0f });
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	OperatePlaceContainer::~OperatePlaceContainer()
	{
		container.clear();
	}

	/**************************************
	�v���C�X�ǉ��J�n����
	***************************************/
	bool OperatePlaceContainer::BeginRoute(PlaceModel * place)
	{
		//���[�g���n�߂���v���C�X�ł��邩�m�F
		if (!place->CanStartRoute())
			return false;

		//�R���e�i�ɒǉ�����return true
		container.push_back(place);
		CreatePin(place, BuildRoad);
		return true;
	}

	/**************************************
	�v���C�X�ǉ��J�n����
	***************************************/
	bool OperatePlaceContainer::BeginDevelop(PlaceModel * place)
	{
		//�J���\�^�C�v�ȊO���m�F
		if (place->IsDevelopableType())
			return false;

		//�R���e�i�ɒǉ�����return true
		container.push_back(place);
		CreatePin(place, Develop);

		return true;
	}

	/**************************************
	�v���C�X�ǉ�����
	***************************************/
	bool OperatePlaceContainer::AddRoute(PlaceModel * place)
	{
		//�d���m�F
		auto itr = std::find(container.begin(), container.end(), place);
		if (itr != container.end())
			return false;

		//�אڔ���
		Adjacency adjacency = place->IsAdjacent(container.back());
		if (adjacency == Adjacency::NotAdjacenct)
			return false;

		//���ɏo���邩
		if (!place->ChangeableRoad(adjacency))
			return false;

		//�ǉ�����return true
		container.push_back(place);
		CreatePin(place, BuildRoad);

		return true;
	}

	/**************************************
	�v���C�X�ǉ�����
	***************************************/
	bool OperatePlaceContainer::AddDevelop(PlaceModel * place)
	{
		//�d���m�F
		auto itr = std::find(container.begin(), container.end(), place);
		if (itr != container.end())
			return false;

		//�אڔ���
		if (place->IsAdjacent(container.back()) == Adjacency::NotAdjacenct)
			return false;

		//�ǉ�����return true
		container.push_back(place);
		CreatePin(place, Develop);

		return true;
	}

	/**************************************
	�ǉ��I������
	***************************************/
	bool OperatePlaceContainer::EndRoute()
	{
		//���[�g����������v���C�X�̐�
		const int validContainerSize = 2;

		//�v���C�X������Ă��Ȃ���΃R���e�i���N���A����return false
		if (container.size() < validContainerSize)
		{
			container.clear();
			actorContainer.clear();
			return false;
		}

		//�Ō�ɒǉ������v���C�X�����[�g���n�߂���^�C�v�łȂ����return false
		PlaceModel* last = *container.rbegin();
		if (!last->CanStartRoute())
		{
			container.clear();
			actorContainer.clear();
			return false;
		}

		return true;
	}

	/**************************************
	�ǉ��I������
	***************************************/
	bool OperatePlaceContainer::EndDevelop()
	{
		//�J��\�^�C�v�ȊO��2�ȏ�܂܂�Ă��Ȃ���΃R���e�i���N���A����return false
		int cntNonDevelopable = 
			from(container) >>
			where([](auto& place) { return !place->IsDevelopableType(); }) >>
			count();

		if (cntNonDevelopable < 2)
		{
			container.clear();
			actorContainer.clear();
			return false;
		}

		return true;
	}

	/**************************************
	�R���e�i�N���A����
	***************************************/
	void OperatePlaceContainer::Clear()
	{
		container.clear();
		std::vector<PlaceModel*>().swap(container);
		actorContainer.clear();
	}

	/**************************************
	�R���e�i�擾����
	***************************************/
	std::vector<PlaceModel*> OperatePlaceContainer::GetPlaces()
	{
		return container;
	}

	/**************************************
	�X�V����
	***************************************/
	void Field::Model::OperatePlaceContainer::Update()
	{
		for (auto&& actor : actorContainer)
		{
			actor->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void OperatePlaceContainer::Draw()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		for (auto&& actor : actorContainer)
		{
			actor->Draw();
		}
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	/**************************************
	�s���A�N�^�[�쐬����
	***************************************/
	void Field::Model::OperatePlaceContainer::CreatePin(const PlaceModel * place, Mode mode)
	{
		PinActor *actor = new PinActor(place->GetPosition().ConvertToWorldPosition() + Vector3::Up * 5.0f, mode);
		actorContainer.push_back(std::unique_ptr<PinActor>(actor));
	}

	/**************************************
	PinActor�R���X�g���N�^
	***************************************/
	PinActor::PinActor(const D3DXVECTOR3& position, OperatePlaceContainer::Mode mode)
	{
		polygon = new BoardPolygon();
		polygon->SetTexDiv({ 2.0f, 1.0f });
		polygon->SetTextureIndex(mode);
		ResourceManager::Instance()->GetPolygon("PinActor", polygon);
		Tween::Move(*this, position + Vector3::Up * 10.0f, position, 30, EaseType::OutCubic);
	}

	/**************************************
	PinActor�f�X�g���N�^
	***************************************/
	PinActor::~PinActor()
	{
		SAFE_DELETE(polygon);
	}

	/**************************************
	PinActor�X�V����
	***************************************/
	void Field::Model::PinActor::Update()
	{
		transform->Rotate(10.0f, Vector3::Up);
	}

	/**************************************
	PinActor�`�揈��
	***************************************/
	void PinActor::Draw()
	{
		polygon->Draw(transform->GetMatrix());
	}
}