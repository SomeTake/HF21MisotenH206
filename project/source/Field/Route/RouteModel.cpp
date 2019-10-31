//=====================================
//
//RouteModel.cpp
//�@�\:�q����������\�����f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "RouteModel.h"
#include "../Place/FieldPlaceModel.h"
#include "../../../Library/cppLinq/cpplinq.hpp"
#include "../../../Framework/Pattern/Delegate.h"
#include "../Place/FieldTownModel.h"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using�錾
	***************************************/
	using cpplinq::last_or_default;
	using cpplinq::from;
	using cpplinq::contains;

	/**************************************
	static�ϐ�
	***************************************/
	unsigned RouteModel::incrementID = 0;

	/**************************************
	�R���X�g���N�^
	***************************************/
	RouteModel::RouteModel(DelegatePlace *onConnectTown, DelegatePlace *onCreateJunction) :
		edgeStart(nullptr), edgeEnd(nullptr),
		uniqueID(incrementID++),
		isUnused(false),
		onConnectedTown(onConnectTown),
		onCreateJunction(onCreateJunction)
	{

	}

	/**************************************
	���n��r���Z�q
	***************************************/
	bool RouteModel::operator==(const RouteModel & rhs) const
	{
		return route == rhs.route;
	}

	/**************************************
	�X�}�[�g�|�C���^�쐬����
	***************************************/
	RouteModelPtr RouteModel::Create(DelegatePlace *onConnectTown, DelegatePlace *onCreateJunction)
	{
		RouteModelPtr ptr = std::make_shared<RouteModel>(onConnectTown, onCreateJunction);
		return ptr;
	}

	/**************************************
	�X�}�[�g�|�C���^�쐬����
	***************************************/
	RouteModelPtr RouteModel::Create(DelegatePlace *onConnectTown, DelegatePlace *onCreateJunction, const std::vector<PlaceModel*>& placeVector)
	{
		RouteModelPtr ptr = std::make_shared<RouteModel>(onConnectTown, onCreateJunction);

		ptr->route.assign(placeVector.begin(), placeVector.end());

		for (auto&& place : ptr->route)
		{
			place->BelongRoute(ptr);
		}

		return ptr;
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	RouteModel::~RouteModel()
	{
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
		place->BelongRoute(shared_from_this());
	}

	/**************************************
	�v���C�X�̏�������
	***************************************/
	void RouteModel::BreakAway()
	{
		//���g�ɏ������Ă���v���C�X�̏���������
		edgeStart->ExitRoute(shared_from_this());
		edgeEnd->ExitRoute(shared_from_this());
		for (auto&& place : route)
		{
			place->ExitRoute(shared_from_this());
		}
	}

	/**************************************
	�אڃ��[�g�ǉ�
	***************************************/
	void RouteModel::AddAdjacency(PlaceModel * junction, PlaceModel * connectTarget, std::shared_ptr<RouteModel> opponent)
	{
		if (*opponent == *this)
			return;

		for (auto&& adjacenct : adjacentRoute)
		{
			std::shared_ptr<RouteModel> sptr = adjacenct.route.lock();

			if (sptr && *sptr == *opponent)
				return;
		}

		adjacentRoute.push_back(AdjacentRoute(junction, connectTarget, opponent));
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

		edge->BelongRoute(shared_from_this());
	}

	/**************************************
	�[�_�ݒ�
	***************************************/
	void RouteModel::SetEdge()
	{
		//�n�_����[�_��ݒ�
		PlaceModel* first = route.front();
		_SetEdge(first);

		//�I�_����[�_��ݒ�
		PlaceModel* last = route.back();
		_SetEdge(last);

		//�e�v���C�X�̕���������
		unsigned routeSize = route.size();

		first->AddDirection(first->IsAdjacent(edgeStart));
		first->AddDirection(first->IsAdjacent(route[1]));

		for (unsigned i = 1; i < routeSize - 1; i++)
		{
			PlaceModel* place = route[i];
			place->AddDirection(place->IsAdjacent(route[i - 1]));
			place->AddDirection(place->IsAdjacent(route[i + 1]));
		}

		last->AddDirection(last->IsAdjacent(route[routeSize - 2]));
		last->AddDirection(last->IsAdjacent(edgeEnd));
	}

	/**************************************
	�����̒[�_�擾
	***************************************/
	PlaceModel * RouteModel::GetOtherEdge(const PlaceModel * edge)
	{
		if (edgeStart == edge)
			return edgeEnd;
		else
			return edgeStart;
	}

	/**************************************
	�q�����Ă���X���擾
	***************************************/
	PlaceModel * RouteModel::GetConnectedTown(const PlaceModel * self)
	{
		if (edgeStart->IsType(PlaceType::Town) && edgeStart != self)
			return edgeStart;

		if (edgeEnd->IsType(PlaceType::Town) && edgeEnd != self)
			return edgeEnd;

		return nullptr;
	}

	/**************************************
	�q�����Ă���X���擾
	***************************************/
	int RouteModel::FindLinkedTown(TownModel * root, std::vector<RouteModelPtr> & searchedRoute, std::vector<const PlaceModel*>& searchedTown, RoutePlaceStack& stackRoute, const PlaceModel* start)
	{
		int cntTown = 0;

		//���[�g�X�^�b�N�Ɏ��g��ς�
		int cntPush = stackRoute.Push(GetAllPlaces(start));

		//�ΏۂɌq�����Ă���X���m�F
		searchedRoute.push_back(shared_from_this());

		const PlaceModel* town = this->GetConnectedTown(root->GetPlace());
		if (town != nullptr)
		{
			cntTown++;
			searchedTown.push_back(town);

			//�o�H��ۑ�
			root->AddLinkedRoute(stackRoute.route);
		}
		else
		{
			//�אڂ��Ă��郋�[�g�ɑ΂��čċA�I�ɒT��
			for (auto&& adjacency : this->adjacentRoute)
			{
				if (adjacency.start == start)
					continue;

				RouteModelPtr ptr = adjacency.route.lock();

				if (!ptr)
					continue;

				if (Utility::IsContain(searchedRoute, ptr))
					continue;

				cntTown += ptr->FindLinkedTown(root, searchedRoute, searchedTown, stackRoute, adjacency.end);
			}
		}
		//�X�^�b�N���玩�g����菜��
		stackRoute.Pop(cntPush);

		return cntTown;
	}

	/**************************************
	�g�p����Z�b�g����
	***************************************/
	void RouteModel::SetUnused(bool use)
	{
		isUnused = use;
	}

	/**************************************
	�g�p����
	***************************************/
	bool RouteModel::IsUnused()
	{
		return isUnused;
	}

	/**************************************
	�S�v���C�X�擾
	***************************************/
	const std::vector<const PlaceModel*> RouteModel::GetAllPlaces(const PlaceModel* start) const
	{
		std::vector<const PlaceModel*> out;
		out.reserve(route.size() + 2);

		if (start == edgeEnd)
		{
			out.push_back(edgeEnd);
			std::copy(route.rbegin(), route.rend(), std::back_inserter(out));
			out.push_back(edgeStart);
		}
		else
		{
			out.push_back(edgeStart);

			std::copy(route.begin(), route.end(), std::back_inserter(out));
			out.push_back(edgeEnd);
		}

		return out;
	}

	/**************************************
	�n�_�擾����
	***************************************/
	PlaceModel * RouteModel::GetFirst() const
	{
		return route.front();
	}

	/**************************************
	�I�_�擾����
	***************************************/
	PlaceModel * RouteModel::GetLast() const
	{
		return route.back();
	}

	/**************************************
	�[�_�ݒ�i���������j
	***************************************/
	void RouteModel::_SetEdge(PlaceModel* place)
	{
		//�A��������擾
		PlaceModel* opponent = place->GetEdgeOpponent();
		SetEdge(opponent);
		opponent->BelongRoute(shared_from_this());

		//�X�Ȃ�o���𑝂₷
		if (opponent->IsType(PlaceType::Town))
			(*onConnectedTown)(opponent);

		//�����_�Ȃ珊�����[�g��ǉ�
	}

	/**************************************
	Place�v�b�V������
	***************************************/
	bool RoutePlaceStack::Push(const PlaceModel * place)
	{
		//���͒ǉ����Ȃ�
		if (place->IsType(PlaceType::Bridge))
			return false;

		if (place->IsType(PlaceType::Road))
		{
			std::vector<Adjacency> AdjacencyType = place->GetConnectingAdjacency();
			StraightType straightType = IsStraight(AdjacencyType);

			//�������Ȃ�ǉ����Ȃ�
			if (straightType != StraightType::NotStraight)
				return false;
		}

		route.push_back(place->GetPosition().ConvertToWorldPosition());
		return true;
	}

	/**************************************
	Place�v�b�V������
	***************************************/
	int RoutePlaceStack::Push(const std::vector<const PlaceModel*>& route)
	{
		int cntPush = 0;
		for (auto&& place : route)
		{
			if (Push(place))
				cntPush++;
		}

		return cntPush;
	}

	/**************************************
	Place�|�b�v����
	***************************************/
	void RoutePlaceStack::Pop()
	{
		route.pop_back();
	}

	/**************************************
	Place�|�b�v����
	***************************************/
	void RoutePlaceStack::Pop(int num)
	{
		route.resize(route.size() - num);
	}

	/**************************************
	�T�C�Y�擾����
	***************************************/
	unsigned RoutePlaceStack::Size() const
	{
		return route.size();
	}
}