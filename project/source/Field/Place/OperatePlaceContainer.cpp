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
#include "../Object/WaterHeightController.h"

#include "../../../Library/cppLinq/cpplinq.hpp"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Particle/BaseEmitter.h"
#include "../../../Framework/Tween/Tween.h"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	static�����o
	***************************************/
	const int OperatePlaceContainer::DurationMoveEmitter = 5;

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

		emitter = GameParticleManager::Instance()->Generate(GameParticle::RouteTrace, Vector3::Zero);
		emitter->SetActive(false);
		effectPinIndex = 0;

		onReachEmitter = std::bind(&OperatePlaceContainer::_OnReachEmitter, this);
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
	bool OperatePlaceContainer::BeginRoute(PlaceModel * place, bool isSea)
	{
		//���[�g���n�߂���v���C�X�ł��邩�m�F
		if (!place->CanStartRoute())
			return false;

		SE::Play(SoundConfig::Select02, 0.5f);

		//�R���e�i�ɒǉ�����return true
		container.push_back(place);
		CreatePin(place, BuildRoad, isSea);

		return true;
	}

	/**************************************
	�v���C�X�ǉ��J�n����
	***************************************/
	bool OperatePlaceContainer::BeginDevelop(PlaceModel * place, bool isSea)
	{
		//�J���\�^�C�v�ȊO���m�F
		if (place->IsDevelopableType())
			return false;

		SE::Play(SoundConfig::Select03, 0.5f);

		//�R���e�i�ɒǉ�����return true
		container.push_back(place);
		CreatePin(place, Develop, isSea);

		return true;
	}

	/**************************************
	�v���C�X�ǉ�����
	***************************************/
	bool OperatePlaceContainer::AddRoute(PlaceModel * place, bool isSea)
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
		CreatePin(place, BuildRoad, isSea);
		
		return true;
	}

	/**************************************
	�v���C�X�ǉ�����
	***************************************/
	bool OperatePlaceContainer::AddDevelop(PlaceModel * place, bool isSea)
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
		CreatePin(place, Develop, isSea);

		return true;
	}

	/**************************************
	�ǉ��I������
	***************************************/
	bool OperatePlaceContainer::EndRoute()
	{
		if (container.size() == 1)
		{
			//�[�_�����ꂼ��ʂ̃v���C�X��
			std::vector<PlaceModel*> connectTarget = container.back()->GetEdgeOpponents();
			if (connectTarget.size() > 1)
				return true;
		}
		else
		{
			//�Ō�ɒǉ������v���C�X�����[�g���n�߂���^�C�v�łȂ����return false
			PlaceModel* last = *container.rbegin();
			if (!last->CanStartRoute())
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		return false;
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

		if (emitter != nullptr)
		{
			emitter->SetActive(false);
		}

		emitter->SetActive(false);
		effectPinIndex = 0;
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

		cntFrame = Math::WrapAround(0, 60, ++cntFrame);
		if (cntFrame == 0)
			StartEmitterMoving();
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
	void Field::Model::OperatePlaceContainer::CreatePin(const PlaceModel * place, Mode mode, bool isSea)
	{
		D3DXVECTOR3 offset = place->IsType(PlaceType::Mountain) ? Vector3::Up * 15.0f : Vector3::Up * 5.0f;
		PinActor *actor = new PinActor(place->GetPosition().ConvertToWorldPosition() + offset, mode, isSea);
		actorContainer.push_back(std::unique_ptr<PinActor>(actor));
	}

	/**************************************
	���[�g�G�t�F�N�g�ړ��J�n����
	***************************************/
	void Field::Model::OperatePlaceContainer::StartEmitterMoving()
	{
		if (actorContainer.size() < 2)
			return;

		if (emitter->IsActive())
			return;

		D3DXVECTOR3 pinPosition = actorContainer[0]->GetPosition();
		emitter->SetActive(true);
		emitter->SetPosition(pinPosition);

		D3DXVECTOR3 nextPosition = actorContainer[1]->GetPosition();
		Tween::Move(*emitter, nextPosition, DurationMoveEmitter, EaseType::Linear, onReachEmitter);

		effectPinIndex = 1;
	}

	/**************************************
	�G�~�b�^�[�����R�[���o�b�N
	***************************************/
	void Field::Model::OperatePlaceContainer::_OnReachEmitter()
	{
		effectPinIndex++;

		if (effectPinIndex < (int)actorContainer.size())
		{
			D3DXVECTOR3 position = actorContainer[effectPinIndex]->GetPosition();
			Tween::Move(*emitter, position, DurationMoveEmitter, EaseType::Linear, onReachEmitter);
		}
		else
		{
			effectPinIndex = 0;
			emitter->SetActive(false);
		}
	}

	/**************************************
	PinActor�R���X�g���N�^
	***************************************/
	PinActor::PinActor(const D3DXVECTOR3& position, OperatePlaceContainer::Mode mode, bool isSea) :
		isSea(isSea)
	{
		polygon = new BoardPolygon();
		polygon->SetTexDiv({ 2.0f, 1.0f });
		polygon->SetTextureIndex(mode);

		ResourceManager::Instance()->GetPolygon("PinActor", polygon);

		transform->SetPosition(position);
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
		//�C�ゾ�����獂���𐅖ʂɍ��킹��
		if (isSea)
		{
			D3DXVECTOR3 position = transform->GetPosition();
			position.y = WaterHeightController::GetHeight() + 5.0f;
			transform->SetPosition(position);
		}
		polygon->Draw(transform->GetMatrix());
	}
}