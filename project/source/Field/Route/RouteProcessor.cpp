
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
	�V������������[�g�ɑ΂��ėאڂ��Ă��郋�[�g�ƘA�������ĉ��H����
	***************************************/
	void RouteProcessor::Process(RouteModelPtr & model, RouteContainer & routeContainer)
	{
		//�����������[�g�̃��X�g
		RouteContainer divideList;

		//�Ώۂ̃��[�g��Place�ɑ΂���1���אڃ��[�g���m�F����
		std::vector<PlaceModel*> route = model->route;
		for (auto&& place : route)
		{
			PlaceModel* connectTarget = place->GetConnectTarget();

			//�A���ΏۂȌ�����Ȃ������̂ŃR���e�B�j���[
			if (connectTarget == nullptr)
				continue;

			//�Ώۂ�Place�������_�ɂ��ĕ���
			place->SetType(PlaceType::Junction);
			divideList = Divide(model, place, routeContainer);

			//�q������������K�v�ł���Ε�������
			RouteContainer subDivList;
			if (connectTarget->IsType(PlaceType::Road))
			{
				connectTarget->SetType(PlaceType::Junction);

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
				Process(divModel, routeContainer);
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
			_ConnectWithEdge(model, start, routeContainer);
		}

		//�I�_�̘A�����m�F
		PlaceModel* end = model->edgeEnd;
		if (end->IsType(PlaceType::Road) || end->IsType(PlaceType::Junction))
		{
			_ConnectWithEdge(model, end, routeContainer);
		}
	}

	/**************************************
	���[�g���w�肵���v���C�X�ŕ�������
	***************************************/
	RouteContainer RouteProcessor::Divide(RouteModelPtr & model, PlaceModel * junction, RouteContainer & routeContainer)
	{
		//������͎g�p���Ȃ��Ȃ�̂Ńt���O�𗧂Ă�
		model->SetUnused(true);

		//�����_����ɂ��ă��[�g�𕪊�
		std::vector<PlaceModel*> route = model->route;
		auto itrJunction = std::find(route.begin(), route.end(), junction);

		std::vector<PlaceModel*> firstHalf, secondHalf;
		firstHalf.assign(route.begin(), itrJunction);
		secondHalf.assign(itrJunction + 1, route.end());		//Junction���܂߂����̂ŃC�e���[�^��+1

		//�O����RouteModel���쐬
		RouteModelPtr first = RouteModel::Create(firstHalf);
		first->SetEdge(model->edgeStart);
		first->SetEdge(junction);

		//�㔼��RouteModel���쐬
		RouteModelPtr second = RouteModel::Create(secondHalf);
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
	�q�����Ă���X��T������
	***************************************/
	int RouteProcessor::FindConnectingTown(PlaceModel * root, RouteModelPtr target, RouteContainer & searchedRoute, std::vector<PlaceModel*> searchedTown)
	{
		int cntTown = 0;

		//�ΏۂɌq�����Ă���X���m�F
		if (!(from(searchedRoute) >> contains(target)))
		{
			searchedRoute.push_back(target);

			PlaceModel* town = target->GetConnectedTown(root);
			if (town != nullptr && !(from(searchedTown) >> contains(town)))
			{
				cntTown++;
				searchedTown.push_back(town);
			}
		}

		//�אڂ��Ă��郋�[�g�ɑ΂��čċA�I�ɒT��
		for (auto&& adjacency : target->adjacentRoute)
		{
			RouteModelPtr ptr = adjacency.route.lock();

			if (!ptr)
				continue;

			if (from(searchedRoute) >> contains(ptr))
				continue;

			cntTown += FindConnectingTown(root, ptr, searchedRoute, searchedTown);
		}

		return cntTown;
	}

	/**************************************
	�A�������i�����j
	***************************************/
	void RouteProcessor::_ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer)
	{
		//�A���Ώۂ����Ȃ�����_�ɂ��ă��[�g�𕪊�
		if (place->IsType(PlaceType::Road))
		{
			place->SetType(PlaceType::Junction);
			RouteContainer targetList = place->GetConnectingRoutes();

			//�擾�����������X�g�ɐV������������[�g���܂܂��̂ō폜
			targetList.erase(std::remove(targetList.begin(), targetList.end(), model));

			//����𕪊�
			RouteContainer divList = Divide(*targetList.begin(), place, routeContainer);
		}

		//�A������ƍ�������[�g�̗אڏ����쐬
		RouteContainer routeList = place->GetConnectingRoutes();
		for (auto&& route : routeList)
		{
			//NOTE:�אڂ̒[�_�������Ȃ̂͂܂���
			model->AddAdjacency(place, place, route);
			route->AddAdjacency(place, place, model);
		}

		//�������X�V(�����ŏd���m�F�����Ă���̂ŎG�ɓ˂�����)
		//�悭�l�����炢��Ȃ��C������̂ŃR�����g�A�E�g
		//place->BelongRoute(place->GetConnectingRoutes());

		//�I�u�W�F�N�g�ݒ�			
	}
}