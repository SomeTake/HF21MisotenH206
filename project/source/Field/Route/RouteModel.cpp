//=====================================
//
//RouteModel.cpp
//�@�\:�q����������\�����f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "RouteModel.h"
#include "../Place/FieldPlaceModel.h"
#include "./../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using�錾
	***************************************/
	using cpplinq::last_or_default;

	/**************************************
	static�ϐ�
	***************************************/
	unsigned RouteModel::incrementID = 0;

	/**************************************
	�R���X�g���N�^
	***************************************/
	RouteModel::RouteModel() :
		edgeStart(nullptr), edgeEnd(nullptr),
		uniqueID(incrementID++)
	{

	}

	/**************************************
	�R���X�g���N�^
	***************************************/
	RouteModel::RouteModel(const std::vector<PlaceModel*>& placeVector) :
		edgeStart(nullptr), edgeEnd(nullptr),
		uniqueID(incrementID++)
	{
		route.assign(placeVector.begin(), placeVector.end());

		for (auto&& place : route)
		{
			place->BelongRoute(this);
		}
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	RouteModel::~RouteModel()
	{
		//���g�ɏ������Ă���v���C�X�̏���������
		edgeStart->ExitRoute(this);
		edgeEnd->ExitRoute(this);
		for (auto&& place : route)
		{
			place->ExitRoute(this);
		}

		adjacentRoute.clear();
		route.clear();
	}

	/**************************************
	�X�V����
	***************************************/
	void RouteModel::Update()
	{
		//�g�p����Ă��Ȃ����[�g���f����אڃ��X�g����폜
		auto itr = std::remove_if(adjacentRoute.begin(), adjacentRoute.end(), [](AdjacentRoute& adjacaency)
		{
			return adjacaency.route.expired();
		});
		adjacentRoute.erase(itr, adjacentRoute.end());
	}

	/**************************************
	���ƂȂ�v���C�X�ǉ�
	***************************************/
	void RouteModel::AddRoad(PlaceModel * place)
	{
		edgeEnd = place;
		route.push_back(place);
		place->BelongRoute(this);
	}

	/**************************************
	�אڃ��[�g�ǉ�
	***************************************/
	void RouteModel::AddAdjacency(PlaceModel * junction, PlaceModel * connectTarget, std::shared_ptr<RouteModel> opponent)
	{
		adjacentRoute.push_back(AdjacentRoute(junction, connectTarget, opponent));
	}

	/**************************************
	�אڃ��[�g�ǉ�
	***************************************/
	void RouteModel::AddAdjacency(const std::vector<AdjacentRoute>& adjacenctRoute)
	{
		std::copy(adjacenctRoute.begin(), adjacenctRoute.end(), std::back_inserter(this->adjacentRoute));
	}

	/**************************************
	�[�_�ݒ�
	***************************************/
	void RouteModel::SetEdge(PlaceModel * edge)
	{
		if (edgeStart == nullptr)
			edgeStart = edge;
		else
			edgeEnd = edge;

		edge->BelongRoute(this);
	}

	/**************************************
	�[�_�ݒ�
	***************************************/
	void RouteModel::SetEdge()
	{
		//�n�_����[�_��ݒ�
		PlaceModel* first = *route.begin();
		_SetEdge(first);

		//�I�_����[�_��ݒ�
		PlaceModel* last = *route.rbegin();
		_SetEdge(last);
	}

	/**************************************
	�[�_�擾
	***************************************/
	PlaceModel * RouteModel::GetEdge(Edge type)
	{
		if (type == Edge::Start)
			return edgeStart;
		else
			return edgeEnd;
	}

	/**************************************
	�����̒[�_�擾
	***************************************/
	PlaceModel * RouteModel::GetOtherEdge(PlaceModel * edge)
	{
		if (edgeStart == edge)
			return edgeEnd;
		else
			return edgeStart;
	}

	/**************************************
	�q�����Ă���X���擾
	***************************************/
	PlaceModel * RouteModel::GetConnectedTown(PlaceModel * self)
	{
		if (edgeStart->IsType(PlaceType::Town) && edgeStart != self)
			return edgeStart;
		
		if (edgeEnd->IsType(PlaceType::Town) && edgeEnd != self)
			return edgeEnd;

		return nullptr;
	}

	/**************************************
	���[�g�擾�i�[�_�͊܂܂Ȃ��j
	***************************************/
	std::vector<PlaceModel*> RouteModel::GetRoute()
	{
		return route;
	}

	/**************************************
	�אڃ��[�g�擾
	***************************************/
	std::vector<AdjacentRoute> RouteModel::GetAdjacencies()
	{
		return adjacentRoute;
	}

	/**************************************
	�[�_�ݒ�i���������j
	***************************************/
	void RouteModel::_SetEdge(PlaceModel* place)
	{
		//�A��������擾
		PlaceModel* opponent = place->GetEdgeOpponent();
		SetEdge(opponent);
		opponent->BelongRoute(this);

		//TODO:�X�Ȃ�o���𑝂₷
	}
}