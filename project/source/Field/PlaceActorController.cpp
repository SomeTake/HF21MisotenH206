//=====================================
//
//PlaceActorController.cpp
//�@�\:�v���C�X�A�N�^�[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlaceActorController.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "FieldConfig.h"
#include "../../Framework/Task/TaskManager.h"
#include "../Effect/GameParticleManager.h"
#include "Along\AlongController.h"
#include "AStar\AStarController.h"
#include "../FieldObject/PassengerController.h"
#include "../../Framework/Resource/ResourceManager.h"

#include "Object/CityBackGroundContainer.h"
#include "Object/WorldBackGroundContainer.h"
#include "Object/SpaceBackGroundContainer.h"

#include "../FieldObject/Actor/CityActor.h"
#include "../FieldObject/Actor/CrossJunctionActor.h"
#include "../FieldObject/Actor/CurveRoadActor.h"
#include "../FieldObject/Actor/MountainActor.h"
#include "../FieldObject/Actor/RiverActor.h"
#include "../FieldObject/Actor/StraightRoadActor.h"
#include "../FieldObject/Actor/TJunctionActor.h"
#include "../FieldObject/Actor/BridgeActor.h"
#include "../FieldObject/Actor/NoneActor.h"

#include "../FieldObject/Animation/ActorAnimation.h"
#include "ActorLoader.h"
#include "../Field/Object/WaterHeightController.h"

namespace Field::Actor
{
	/**************************************
	using�錾
	***************************************/
	using Model::PlaceType;
	using Model::Adjacency;

	/**************************************
	static�����o
	***************************************/
	const float PlaceActorController::PlacePositionOffset = 10.0f;
	const D3DXVECTOR3 PlaceActorController::PositionEmitSmog = Vector3::Up;
	const unsigned PlaceActorController::ReserveGround = 2500;

	/**************************************
	�R���X�g���N�^
	***************************************/
	PlaceActorController::PlaceActorController(Field::FieldLevel level) :
		currentLevel(level),
		bonusSideWay(0.0f)
	{
		alongController = new Along::AlongController(level);
		aStarController = new Route::AStarController();
		passengerController = new PassengerController(currentLevel);

		switch (level)
		{
		case FieldLevel::City:
			bgContainer = new CityBackGroundContainer();
			break;

		case FieldLevel::World:
			bgContainer = new WorldBackGroundContainer();
			break;

		case FieldLevel::Space:
			bgContainer = new SpaceBackGroundContainer();
			break;

		default:
			bgContainer = new CityBackGroundContainer();
			break;
		}

		auto onReachPassenger = std::bind(&Along::AlongController::OnReachPassenger, alongController, std::placeholders::_1);
		passengerController->SetCallbackOnReach(onReachPassenger);

		alongController->SetBuildBonusFunc([this]()
		{
			bonusSideWay += 1.0f;
		});

		//�����x���̃��f���������̂ň�U�A�X���x���ɗ��Ƃ�
		if (currentLevel == FieldLevel::World)
			currentLevel = FieldLevel::City;
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	PlaceActorController::~PlaceActorController()
	{
		SAFE_DELETE(alongController);
		SAFE_DELETE(aStarController);
		SAFE_DELETE(passengerController);
		SAFE_DELETE(bgContainer);

		actorContainer.clear();
	}

	/**************************************
	�X�V����
	***************************************/
	void PlaceActorController::Update()
	{
		alongController->Update();
		passengerController->Update();

		WaterHeightController::UpdateHeight();
	
		bgContainer->Update();

		for (auto&& actor : actorContainer)
		{
			actor.second->Update();
		}

		for (auto&& actor : poolDestroy)
		{
			actor.second->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void PlaceActorController::Draw()
	{

		for (auto&& actor : actorContainer)
		{
			actor.second->Draw();
		}

		for (auto&& actor : poolDestroy)
		{
			actor.second->Draw();
		}

		alongController->Draw();
		passengerController->Draw();

		//bgContainer->Draw();
	}

	/**************************************
	���\�[�X�ǂݍ��ݏ���
	***************************************/
	void PlaceActorController::LoadResource()
	{
		// 3D�I�u�W�F�N�g�̃��\�[�X�����[�h
		ResourceManager::Instance()->LoadMesh("NoneActor", "data/MODEL/PlaceActor/ground.x");
		ResourceManager::Instance()->LoadMesh("River-City", "data/MODEL/PlaceActor/river.x");
		ResourceManager::Instance()->LoadMesh("AlongCity", "data/MODEL/AlongActor/AlongActorCity.x");
		ResourceManager::Instance()->LoadMesh("AlongSpace", "data/MODEL/AlongActor/AlongSpace.x");

		//�A�N�^�[�̃��\�[�X�����[�h
		ActorLoader loader;
		loader.LoadConfig();
		loader.LoadResource();

		//�w�i�A�N�^�[�����[�h
		bgContainer->Load();

		// �p�b�Z���W���[
		passengerController->LoadResource();
		passengerController->LoadCSV(Field::Const::FieldLayerFile[0]);
	}

	/**************************************
	�A�N�^�[�Z�b�g����
	***************************************/
	void PlaceActorController::SetActor(const Model::PlaceModel * place, int delay)
	{
		const Model::PlaceType Type = place->GetType();

		switch (Type)
		{
		case PlaceType::Bridge:
			SetBridge(place);
			break;

		case PlaceType::Junction:
			SetJunction(place);
			break;

		case PlaceType::Mountain:
			SetMountain(place);
			break;

		case PlaceType::Road:
			SetRoad(place, delay);
			break;

		case PlaceType::Town:
			SetTown(place);
			break;
		}
	}

	/**************************************
	�A�N�^�[�Z�b�g����
	***************************************/
	void PlaceActorController::SetActor(const RouteModelPtr routeModel)
	{
		auto places = routeModel->GetAllPlaces();

		ChangeActor(places.front());
		ChangeActor(places.back());

		unsigned PlaceMax = places.size() - 1;
		for (unsigned i = 1; i < PlaceMax; i++)
		{
			if (places[i]->IsType(PlaceType::Bridge))
				continue;

			SetActor(places[i], i * 2);
		}
	}

	/**************************************
	�A�N�^�[�؂�ւ�����
	***************************************/
	void PlaceActorController::ChangeActor(const Model::PlaceModel * place)
	{
		if (place == nullptr)
			return;

		if (place->IsType(PlaceType::Town))
			return;

		//�A�N�^�[�j��
		EraseFromContainer(place->ID());

		SetActor(place);
	}

	/**************************************
	�A�N�^�[���ŏ���
	***************************************/
	bool PlaceActorController::DestroyActor(const Model::PlaceModel * place)
	{
		unsigned placeID = place->ID();

		if (actorContainer.count(placeID) == 0)
			return false;

		GameParticleManager::Instance()->Generate(GameParticle::WhiteSmog, place->GetPosition().ConvertToWorldPosition());

		//�j���v�[���ֈړ����ăA�N�^�[�R���e�i����폜
		poolDestroy[placeID] = std::move(actorContainer[placeID]);
		actorContainer.erase(placeID);

		//�A�j���[�V���������ďI�����ɉ��
		ActorAnimation::Shrink(*poolDestroy[placeID], [&, placeID]()
		{
			poolDestroy.erase(placeID);
		});

		return true;
	}

	/**************************************
	�������̃I�u�W�F�N�g��������
	***************************************/
	void PlaceActorController::GrowthAlongObject(const D3DXVECTOR3 & position)
	{
		alongController->OnReachPassenger(position);
	}

	/**************************************
	�X���q������
	***************************************/
	void PlaceActorController::OnConnectedTown(const Model::PlaceModel * place)
	{
		aStarController->OnChangePlace(place);
	}

	/**************************************
	�p�b�Z���W���[�o������
	***************************************/
	void PlaceActorController::DepartPassenger(const Model::PlaceModel * start, const Model::PlaceModel * goal, const Model::PlaceModel* town)
	{
		auto route = aStarController->CalcRoute(start->GetPosition(), goal->GetPosition(), town->GetPosition());

		if (route.size() != 0)
		{
			passengerController->SetPassenger(route);
		}
	}

	/**************************************
	�������{�[�i�X�擾����
	***************************************/
	float PlaceActorController::GetSideWayBonus() const
	{
		return bonusSideWay;
	}

	/**************************************
	�C���ǂ����̔���
	***************************************/
	bool PlaceActorController::EnableAtlantis(const FieldPosition & position) const
	{
		return bgContainer->EnableAtlantis(position);
	}

	/**************************************
	�V�����X�쐬
	***************************************/
	PlaceActor* PlaceActorController::CreateNewTown(const Model::PlaceModel * place)
	{
		//�A�N�^�[����
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();
		PlaceActor* actor = new CityActor(actorPos, currentLevel);

		AddContainer(place->ID(), actor);
		aStarController->OnChangePlace(place);

		Tween::Scale(*actor, { 0.25f, 0.0f, 0.25f }, { 0.25f, 0.25f, 0.25f }, 60, EaseType::InCubic);

		return actor;
	}

	/**************************************
	�A�g�����e�B�X�o��
	***************************************/
	void PlaceActorController::SetAtlantis(const Model::PlaceModel * place)
	{
		//�X�쐬
		const D3DXVECTOR3 InitOffset = Vector3::Down * 10.0f;
		PlaceActor* townActor = CreateNewTown(place);

		D3DXVECTOR3 actorPos = townActor->GetPosition();
		Tween::Move(*townActor, actorPos + InitOffset, actorPos, 60, EaseType::InOutCirc);

		//�n�ʐ���
		WorldBackGroundContainer *worldBgContainer = dynamic_cast<WorldBackGroundContainer*>(bgContainer);
		worldBgContainer->CreateAtlantis(place->GetPosition());

		//�p�b�Z���W���[���ɒn�`�̕ω���ʒm
		passengerController->RewriteMap(place->GetPosition(), PassengerController::Geography::Ground);
	}

	/**************************************
	���[�h�Z�b�g����
	***************************************/
	void PlaceActorController::SetRoad(const Model::PlaceModel * place, int delay)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//�A����񂩂�ǂ̃^�C�v�̓����𔻒�
		std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
		StraightType straightType = IsStraight(AdjacencyType);

		bool onWater = bgContainer->IsSeaPlace(place->GetPosition());

		//�����^�C�v�̏ꍇ
		if (straightType != StraightType::NotStraight)
		{
			//�A�N�^�[����
			PlaceActor* actor = new StraightRoadActor(actorPos, currentLevel, onWater);
			AddContainer(place->ID(), actor);

			//���E�Ɍq����^�C�v�Ȃ��]������
			if (straightType == StraightType::RightAndLeft)
				actor->Rotate(90.0f);

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::Straight);

			// �����A�j���[�V����
			actor->SetScale(Vector3::Zero);
			SetRoadGenerateAnimation(actor, actorPos, delay);
		}
		//�J�[�u�̏ꍇ
		else
		{
			//�A�N�^�[����
			PlaceActor* actor = new CurveRoadActor(actorPos, currentLevel, onWater);
			AddContainer(place->ID(), actor);

			//��]�p�x�����肵�ĉ�]
			float rotAngle = 0.0f;

			CurveType curveType = IsCurve(AdjacencyType);
			if (curveType == CurveType::LeftAndForward)
				rotAngle = -90.0f;
			else if (curveType == CurveType::BackAndRight)
				rotAngle = 90.0f;
			else if (curveType == CurveType::ForwardAndRight)
				rotAngle = 180.0f;

			actor->Rotate(rotAngle);

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::Curve);

			// �����A�j���[�V����
			actor->SetScale(Vector3::Zero);
			SetRoadGenerateAnimation(actor, actorPos, delay);
		}

		//A*�ɓo�^
		aStarController->OnChangePlace(place);
	}

	/**************************************
	�^�E���Z�b�g����
	***************************************/
	void PlaceActorController::SetTown(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//�A�N�^�[����
		PlaceActor* actor = new CityActor(actorPos, currentLevel);

		// �����A�j���[�V����
		ActorAnimation::ExpantionYAndReturnToOrigin(*actor);

		AddContainer(place->ID(), actor);

		//A*�ɓo�^
		aStarController->OnChangePlace(place);
	}

	/**************************************
	�u���b�W�Z�b�g����
	***************************************/
	void PlaceActorController::SetBridge(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//�A�N�^�[����
		PlaceActor* actor = new BridgeActor(actorPos, currentLevel);

		//��]�p�x������
		std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
		StraightType straightType = IsStraight(AdjacencyType);

		float rotateAngle = straightType == StraightType::BackAndForward ? 90.0f : 0.0f;

		//��]
		actor->Rotate(rotateAngle);

		// �����A�j���[�V����
		ActorAnimation::FallAndExpantion(*actor);

		AddContainer(place->ID(), actor);

		//A*�ɓo�^
		aStarController->OnChangePlace(place);
	}

	/**************************************
	�����_�Z�b�g����
	***************************************/
	void PlaceActorController::SetJunction(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		std::vector<Adjacency> adjacencyTypeList = place->GetConnectingAdjacency();

		bool onWater = bgContainer->IsSeaPlace(place->GetPosition());

		//�\���H�̃A�N�^�[�쐬
		if (adjacencyTypeList.size() == 4)
		{
			PlaceActor *actor = new CrossJunctionActor(actorPos, currentLevel, onWater);

			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::CrossJunction);

			// �����A�j���[�V����
			ActorAnimation::RotateAndExpantion(*actor);
			AddContainer(place->ID(), actor);

		}
		//T���H�̃A�N�^�[����
		else
		{
			PlaceActor* actor = new TJunctionActor(actorPos, currentLevel, onWater);

			TjunctionType junctionType = IsTjunction(adjacencyTypeList);
			float rotAngle = 0.0f;

			if (junctionType == TjunctionType::ExceptRight)
				rotAngle = 90.0f;
			else if (junctionType == TjunctionType::ExceptForward)
				rotAngle = 180.0f;
			else if (junctionType == TjunctionType::ExceptLeft)
				rotAngle = 270.0f;

			actor->Rotate(rotAngle);

			AddContainer(place->ID(), actor);
			
			alongController->OnBuildRoad(actor->GetTransform(), Along::AlongController::RoadType::T_Junction);

			// �����A�j���[�V����
			ActorAnimation::RotateAndExpantion(*actor);
		}

		//A*�ɓo�^
		aStarController->OnChangePlace(place);
	}

	/**************************************
	�R�Z�b�g����
	***************************************/
	void PlaceActorController::SetMountain(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		PlaceActor *actor = new MountainActor(actorPos, currentLevel);

		//��]
		float rotateAngle = Math::RandomRange(0, 4) * 90.0f;
		actor->Rotate(rotateAngle);

		//�A�j���[�V����
		ActorAnimation::ExpantionYAndReturnToOrigin(*actor);

		AddContainer(place->ID(), actor);
	}

	/**************************************
	�R���e�i�ǉ�����
	***************************************/
	void PlaceActorController::AddContainer(unsigned key, PlaceActor * actor)
	{
		//�d���m�F
		EraseFromContainer(key);

		actorContainer.emplace(key, std::unique_ptr<PlaceActor>(actor));
	}

	/**************************************
	�R���e�i����̍폜����
	***************************************/
	bool PlaceActorController::EraseFromContainer(unsigned key)
	{
		if (actorContainer.count(key) == 0)
			return false;

		//�A�N�^�[�R���e�i����
		actorContainer.erase(key);

		return true;
	}

	/**************************************
	���������̃A�j���[�V�����Z�b�g����
	***************************************/
	void Field::Actor::PlaceActorController::SetRoadGenerateAnimation(PlaceActor * actor, const D3DXVECTOR3 actorPos, int delay)
	{
		if (delay == 0)
			ActorAnimation::FallAndExpantion(*actor, [=]()
		{
			GameParticleManager::Instance()->Generate(GameParticle::ColorfulDebis, actorPos + PositionEmitSmog);
		});

		else
		{
			TaskManager::Instance()->CreateDelayedTask(delay, [=]()
			{
				ActorAnimation::FallAndExpantion(*actor, [=]()
				{
					GameParticleManager::Instance()->Generate(GameParticle::ColorfulDebis, actorPos + PositionEmitSmog);
				});
			});
		}
	}
}