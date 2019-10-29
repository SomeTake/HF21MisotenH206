
//=====================================
//
//RouteProcessor.cpp
//�@�\:���[�g���f���𑀍삷��N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "RouteProcessor.h"
#include "RouteModel.h"
#include "../Place/FieldPlaceModel.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using�錾
	***************************************/
	using cpplinq::from;
	using cpplinq::contains;

	/**************************************
	�R���X�g���N�^
	***************************************/
	RouteProcessor::RouteProcessor(Delegate<void(const PlaceModel*)> *onChangePlaceType)
	{
		this->onChangePlaceType = onChangePlaceType;
	}

	/**************************************
	�V������������[�g�ɑ΂��ėאڂ��Ă��郋�[�g�ƘA�������ĉ��H����
	***************************************/
	void RouteProcessor::Process(RouteModelPtr & model, RouteContainer & routeContainer, std::vector<PlaceModel*> *ignoreList)
	{
		//�����������[�g�̃��X�g
		RouteContainer divideList;

		//�������X�g��NULL�Ȃ�쐬
		if (ignoreList == NULL)
		{
			ignoreList = &model->route;
		}

		//�Ώۂ̃��[�g��Place�ɑ΂���1���אڃ��[�g���m�F����
		std::vector<PlaceModel*> route = model->route;
		for (auto&& place : route)
		{
			//���̏ꍇ�͔��肵�Ȃ�
			if (place->IsType(PlaceType::Bridge))
				continue;

			PlaceModel* connectTarget = place->GetConnectTarget();

			//�A���ΏۂȌ�����Ȃ������̂ŃR���e�B�j���[
			if (connectTarget == nullptr)
				continue;

			//�A���Ώۂ��������X�g�Ɋ܂܂�Ă�����R���e�B�j���[
			if (Utility::IsContain(*ignoreList, connectTarget))
				continue;

			//�Ώۂ�Place�������_�ɂ��ĕ���
			place->SetType(PlaceType::Junction);
			divideList = Divide(model, place, routeContainer);
			(*model->onCreateJunction)(place);

			place->AddDirection(connectTarget);
			connectTarget->AddDirection(place);

			//�q������������K�v�ł���Ε�������
			connectTarget->SetType(PlaceType::Junction);
			RouteContainer subDivList;
			if (connectTarget->GetPrevType() == PlaceType::Road)
			{
				(*model->onCreateJunction)(connectTarget);
				RouteModelPtr opponent = connectTarget->GetConnectingRoute();
				subDivList = Divide(opponent, connectTarget, routeContainer);
			}
			else
			{
				subDivList = connectTarget->GetConnectingRoutes();
			}

			//�q���������[�g���m��אڃ����o�Ƃ��ĕۑ�
			for (auto&& own : divideList)
			{
				for (auto&& other : subDivList)
				{
					own->AddAdjacency(place, connectTarget, other);
					other->AddAdjacency(connectTarget, place, own);
				}
			}

			//����𕪊����Ă����RouteContainer�ɒǉ�
			if (subDivList.size() > 1)
			{
				std::copy(subDivList.begin(), subDivList.end(), std::back_inserter(routeContainer));
			}

			//�������X�V
			RouteContainer belongList = connectTarget->GetConnectingRoutes();
			place->BelongRoute(belongList);

			connectTarget->BelongRoute(divideList);

			//�����_�ƘA���Ώۂ̃I�u�W�F�N�g��ݒ�
			(*onChangePlaceType)(place);
			(*onChangePlaceType)(connectTarget);

			//���[�g�𕪊��������_�Ő���Ƀ��[�v�ł��Ȃ��Ȃ�̂Ńu���C�N
			break;
		}

		//�������s���Ă��Ȃ������烋�[�g�R���e�i�ɒǉ�
		if (divideList.empty())
		{
			routeContainer.push_back(model);
		}
		//�������s���Ă�����ċA�I�ɉ��H����
		else
		{
			for (auto&& divModel : divideList)
			{
				Process(divModel, routeContainer, ignoreList);
			}
		}
	}

	/**************************************
	�V������������[�g��[�_�ŘA��������
	***************************************/
	void RouteProcessor::ConnectWithEdge(RouteModelPtr & model, RouteContainer & routeContainer)
	{
		//�n�_�̘A�����m�F
		PlaceModel* start = model->edgeStart;
		if (start->IsType(PlaceType::Road) || start->IsType(PlaceType::Junction))
		{
			_ConnectWithEdge(model, start, routeContainer, model->GetFirst());
			start->AddDirection(model->route.front());
		}

		//�I�_�̘A�����m�F
		PlaceModel* end = model->edgeEnd;
		if (end->IsType(PlaceType::Road) || end->IsType(PlaceType::Junction))
		{
			_ConnectWithEdge(model, end, routeContainer, model->GetLast());
			end->AddDirection(model->route.back());
		}
	}

	/**************************************
	���[�g���w�肵���v���C�X�ŕ�������
	***************************************/
	RouteContainer RouteProcessor::Divide(RouteModelPtr & model, PlaceModel * junction, RouteContainer & routeContainer)
	{
		//������͎g�p���Ȃ��Ȃ�̂Ńt���O�𗧂ĂāA�v���C�X�̏���������
		model->SetUnused(true);
		model->BreakAway();

		//�����_����ɂ��ă��[�g�𕪊�
		std::vector<PlaceModel*> route = model->route;
		auto itrJunction = std::find(route.begin(), route.end(), junction);

		std::vector<PlaceModel*> firstHalf, secondHalf;
		firstHalf.assign(route.begin(), itrJunction);
		secondHalf.assign(itrJunction + 1, route.end());		//Junction���܂߂Ȃ��̂ŃC�e���[�^��+1

		//�O����RouteModel���쐬
		RouteModelPtr first = RouteModel::Create(model->onConnectedTown, model->onCreateJunction, firstHalf);
		first->SetEdge(model->edgeStart);
		first->SetEdge(junction);

		//�㔼��RouteModel���쐬
		RouteModelPtr second = RouteModel::Create(model->onConnectedTown, model->onCreateJunction, secondHalf);
		second->SetEdge(junction);
		second->SetEdge(model->edgeEnd);

		//�����O�̃��[�g�̗אڃ��[�g���擾
		std::vector<AdjacentRoute> adjacencies = model->adjacentRoute;

		//�אڏ��쐬
		first->AddAdjacency(adjacencies);
		first->AddAdjacency(junction, junction, second);

		second->AddAdjacency(adjacencies);
		second->AddAdjacency(junction, junction, first);

		//�����O�ɗאڂ��Ă������[�g�ɑ΂��ėאڏ���ǉ�
		for (auto&& adjacency : adjacencies)
		{
			PlaceModel* connection = adjacency.start;

			//first��second�̂ǂ����connection���܂܂�Ă��邩����
			RouteModelPtr opponent = from(firstHalf) >> contains(connection) ? first : second;

			std::shared_ptr<RouteModel> sptr = adjacency.route.lock();
			if (sptr)
			{
				sptr->AddAdjacency(adjacency.end, junction, opponent);
			}
		}

		//�������RouteModel�����X�g�ɒǉ�
		RouteContainer routeList{ first, second };

		return routeList;
	}

	/**************************************
	�A�������i�����j
	***************************************/
	void RouteProcessor::_ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer, PlaceModel *edge)
	{
		//����������_�ɕς���K�v�����邩�m�F
		Adjacency adjacency = place->IsAdjacent(edge);
		std::vector<Adjacency> direction = place->GetConnectingAdjacency();
		bool shouldChangeJunction = !Utility::IsContain(direction, adjacency);

		if (shouldChangeJunction)
		{
			place->SetType(PlaceType::Junction);
			place->AddDirection(adjacency);
			(*onChangePlaceType)(place);

			if (place->GetPrevType() == PlaceType::Road)
			{
				(*model->onCreateJunction)(place);

				RouteContainer targetList = place->GetConnectingRoutes();

				//�擾�����������X�g�ɐV������������[�g���܂܂��̂ō폜
				targetList.erase(std::remove(targetList.begin(), targetList.end(), model));

				//����𕪊�
				RouteContainer divList = Divide(*targetList.begin(), place, routeContainer);
			}
		}

		//�A������ƍ�������[�g�̗אڏ����쐬
		RouteContainer routeList = place->GetConnectingRoutes();
		for (auto&& route : routeList)
		{
			model->AddAdjacency(place, place, route);
			route->AddAdjacency(place, place, model);
		}
	}
}