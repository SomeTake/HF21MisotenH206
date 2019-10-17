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

#include "../FieldObject/Actor/CityActor.h"
#include "../FieldObject/Actor/CrossJunctionActor.h"
#include "../FieldObject/Actor/CurveRoadActor.h"
#include "../FieldObject/Actor/MountainActor.h"
#include "../FieldObject/Actor/RiverActor.h"
#include "../FieldObject/Actor/StraightRoadActor.h"
#include "../FieldObject/Actor/TJunctionActor.h"

namespace Field::Actor
{
	/**************************************
	using�錾
	***************************************/
	using Model::PlaceType;
	using Model::Adjacency;

	/**************************************
	using�錾
	***************************************/
	const float PlaceActorController::PlacePositionOffset = 10.0f;

	/**************************************
	�R���X�g���N�^
	***************************************/
	PlaceActorController::PlaceActorController()
	{
		actorContainer.resize(ActorPattern::Max, NULL);

		for (auto&& actorMap : actorContainer)
		{
			actorMap = new ActorMap();
		}
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	PlaceActorController::~PlaceActorController()
	{
		for (auto&& actorMap : actorContainer)
		{
			actorMap->clear();
			SAFE_DELETE(actorMap);
		}
		actorContainer.clear();
	}

	/**************************************
	�X�V����
	***************************************/
	void PlaceActorController::Update()
	{
		//for (auto&& map : actorMap)
		//{
		//	for (auto&& pair : *map)
		//	{
		//		pair.second->Update();
		//	}
		//}
	}

	/**************************************
	�`�揈��
	***************************************/
	void PlaceActorController::Draw()
	{
		//NOTE:�C���X�^���V���O�ŕ`�悷�邽�߂Ɍ��\�����邩��
		for (auto&& map : actorContainer)
		{
			for (auto&& pair : *map)
			{
				pair.second->Draw();
			}
		}
	}

	/**************************************
	�A�N�^�[�Z�b�g����
	***************************************/
	void PlaceActorController::SetActor(const Model::PlaceModel * place)
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

		case PlaceType::River:
			SetRiver(place);
			break;

		case PlaceType::Road:
			SetRoad(place);

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
		for(unsigned i = 1; i < PlaceMax; i++)
		{ 
			SetActor(places[i]);
		}
	}

	/**************************************
	�A�N�^�[�؂�ւ�����
	***************************************/
	void PlaceActorController::ChangeActor(const Model::PlaceModel * place)
	{
		PlaceType PrevType = place->GetPrevType();
		unsigned PlaceID = place->ID();

		bool resultErase = false;

		//�R���e�i����g�p���̃A�N�^�[���폜
		if (PrevType == PlaceType::Road)
		{
			resultErase |= EraseFromContainer(ActorPattern::StarightRoad, PlaceID);
			resultErase |= EraseFromContainer(ActorPattern::Curve, PlaceID);
		}
		else if (PrevType == PlaceType::Junction)
		{
			resultErase |= EraseFromContainer(ActorPattern::TJunction, PlaceID);
			resultErase |= EraseFromContainer(ActorPattern::CrossJunction, PlaceID);
		}

		if (resultErase)
		{
			SetActor(place);
		}
	}

	/**************************************
	���[�h�Z�b�g����
	***************************************/
	void PlaceActorController::SetRoad(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		//�A����񂩂�ǂ̃^�C�v�̓����𔻒�
		std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
		StraightType straightType = IsStraight(AdjacencyType);

		//�����^�C�v�̏ꍇ
		if (straightType != StraightType::NotStraight)
		{
			//�A�N�^�[����
			PlaceActor* actor = new StraightRoadActor(actorPos, Model::FieldLevel::City);

			//���E�Ɍq����^�C�v�Ȃ��]������
			if (straightType == StraightType::RightAndLeft)
				actor->Rotate(90.0f);

			AddContainer(ActorPattern::StarightRoad, place->ID(), actor);
		}
		//�J�[�u�̏ꍇ
		else
		{
			//�A�N�^�[����
			PlaceActor* actor = new CurveRoadActor(actorPos, Model::FieldLevel::City);
			
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

			AddContainer(ActorPattern::Curve, place->ID(), actor);
		}
	}

	/**************************************
	�^�E���Z�b�g����
	***************************************/
	void PlaceActorController::SetTown(const Model::PlaceModel * place)
	{

	}

	/**************************************
	��Z�b�g����
	***************************************/
	void PlaceActorController::SetRiver(const Model::PlaceModel * place)
	{
	}

	/**************************************
	�u���b�W�Z�b�g����
	***************************************/
	void PlaceActorController::SetBridge(const Model::PlaceModel * place)
	{
	}

	/**************************************
	�����_�Z�b�g����
	***************************************/
	void PlaceActorController::SetJunction(const Model::PlaceModel * place)
	{
		D3DXVECTOR3 actorPos = place->GetPosition().ConvertToWorldPosition();

		std::vector<Adjacency> adjacencyTypeList = place->GetConnectingAdjacency();

		//�\���H�̃A�N�^�[�쐬
		if (adjacencyTypeList.size() == 4)
		{
			PlaceActor *actor = new CrossJunctionActor(actorPos, Model::FieldLevel::City);
			AddContainer(ActorPattern::CrossJunction, place->ID(), actor);
		}
		//T���H�̃A�N�^�[����
		else
		{
			PlaceActor* actor = new TJunctionActor(actorPos, Model::FieldLevel::City);
			
			TjunctionType junctionType = IsTjunction(adjacencyTypeList);
			float rotAngle = 0.0f;

			if (junctionType == TjunctionType::ExceptRight)
				rotAngle = 90.0f;
			else if (junctionType == TjunctionType::ExceptBack)
				rotAngle = 180.0f;
			else if (junctionType == TjunctionType::ExceptLeft)
				rotAngle = -90.0f;
	
			actor->Rotate(rotAngle);

			AddContainer(ActorPattern::TJunction, place->ID(), actor);
		}
	}

	/**************************************
	�R�Z�b�g����
	***************************************/
	void PlaceActorController::SetMountain(const Model::PlaceModel * place)
	{
	}

	/**************************************
	�R���e�i�ǉ�����
	***************************************/
	void PlaceActorController::AddContainer(ActorPattern pattern, unsigned key, PlaceActor * actor)
	{
		actorContainer[pattern]->emplace(key, actor);
	}

	/**************************************
	�R���e�i����̍폜����
	***************************************/
	bool PlaceActorController::EraseFromContainer(ActorPattern pattern, unsigned key)
	{
		if (actorContainer[pattern]->count(key) == 0)
			return false;

		actorContainer[pattern]->erase(key);
		return true;
	}
}