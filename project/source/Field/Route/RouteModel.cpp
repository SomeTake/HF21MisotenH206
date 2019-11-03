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
	RouteModel::RouteModel(Delegate<void(const PlaceModel*, const PlaceModel*)> *onConnectTown, DelegatePlace *onCreateJunction) :
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
	RouteModelPtr RouteModel::Create(Delegate<void(const PlaceModel*, const PlaceModel*)> *onConnectTown, DelegatePlace *onCreateJunction)
	{
		RouteModelPtr ptr = std::make_shared<RouteModel>(onConnectTown, onCreateJunction);
		return ptr;
	}

	/**************************************
	�X�}�[�g�|�C���^�쐬����
	***************************************/
	RouteModelPtr RouteModel::Create(Delegate<void(const PlaceModel*, const PlaceModel*)> *onConnectTown, DelegatePlace *onCreateJunction, const std::vector<PlaceModel*>& placeVector)
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

		if (routeSize != 1)
		{
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
		else
		{
			first->AddDirection(first->IsAdjacent(edgeStart));
			first->AddDirection(first->IsAdjacent(edgeEnd));
		}
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
	int RouteModel::FindLinkedTown(TownModel * root, std::vector<unsigned> & searchedRoute)
	{
		int cntTown = 0;

		//�ΏۂɌq�����Ă���X���m�F
		searchedRoute.push_back(uniqueID);

		const PlaceModel* town = this->GetConnectedTown(root->GetPlace());
		if (town != nullptr)
		{
			cntTown++;

			//�o�H��ۑ�
			root->AddLinkedTown(town);
		}
		else
		{
			//�אڂ��Ă��郋�[�g�ɑ΂��čċA�I�ɒT��
			for (auto&& adjacency : this->adjacentRoute)
			{
				RouteModelPtr ptr = adjacency.route.lock();

				if (!ptr)
					continue;

				if (Utility::IsContain(searchedRoute, ptr->uniqueID))
					continue;

				cntTown += ptr->FindLinkedTown(root, searchedRoute);
			}
		}

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
		PlaceModel* edge = nullptr;
		auto opponents = place->GetEdgeOpponents();
		for (auto&& opponent : opponents)
		{
			if (opponent != edgeEnd && opponent != edgeStart)
			{
				edge = opponent;
				break;
			}
		}

		SetEdge(edge);
		edge->BelongRoute(shared_from_this());

		//�X�Ȃ�o���𑝂₷
		if (edge->IsType(PlaceType::Town))
		{
			//�����ǉ�
			edge->AddDirection(edge->IsAdjacent(place));

			(*onConnectedTown)(edge, place);
		}
	}
}