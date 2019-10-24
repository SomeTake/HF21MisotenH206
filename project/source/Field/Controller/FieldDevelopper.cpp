//=====================================
//
//FieldDevelopper.cpp
//�@�\:�t�B�[���h�J���@�\
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldDevelopper.h"
#include "../Place/FieldPlaceModel.h"
#include "../PlaceActorController.h"
#include "../Place/OperatePlaceContainer.h"
#include "../Route/RouteModel.h"
#include "../Route/RouteProcessor.h"
#include "../Place/FieldPlaceContainer.h"

#include <algorithm>

namespace Field
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldController::FieldDevelopper::FieldDevelopper(FieldController * controller) :
		entity(controller)
	{

	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	FieldController::FieldDevelopper::~FieldDevelopper()
	{
	}

	/**************************************
	�������
	***************************************/
	void FieldController::FieldDevelopper::BuildRoad()
	{
		using namespace Field::Model;

		//����Ώۂ̃v���C�X��Road�^�C�v�ɕϊ�
		std::vector<PlaceModel*> route = entity->operateContainer->GetPlaces();
		for (auto&& place : route)
		{
			if (place->IsType(PlaceType::None))
				place->SetType(PlaceType::Road);
		}

		//���[�g���f���쐬
		RouteModelPtr ptr = RouteModel::Create(entity->onConnectTown, entity->onCreateJunction, route);

		//�[�_�ݒ�
		ptr->SetEdge();

		//�I�u�W�F�N�g�ݒ�

		//�אڂ��郋�[�g�ƘA��������
		entity->routeProcessor->ConnectWithEdge(ptr, entity->routeContainer);
		entity->routeProcessor->Process(ptr, entity->routeContainer);

		//����V����������̂ō��G�x���Čv�Z
		entity->placeContainer->CaclTrafficJamRate();

		//�A�N�^�[����
		entity->placeActController->SetActor(ptr);

		//�R�[���o�b�N
		(*entity->onBuildRoad)(route);
	}

	/**************************************
	�v���C�X�J������
	***************************************/
	void FieldController::FieldDevelopper::DevelopPlace(PlaceVector & route, PlaceIterator start)
	{
		using namespace Field::Model;

		auto head = std::find_if(start, route.end(), [](auto& place)
		{
			return place->IsType(PlaceType::Mountain) || place->IsType(PlaceType::River);
		});

		//�J��Ώۂ�������Ȃ��̂Ń��^�[��
		if (head == route.end())
			return;

		//�R���J��
		if ((*head)->IsType(PlaceType::Mountain))
		{
			head = DevelopMountain(route, head);
		}
		//����J��
		else if ((*head)->IsType(PlaceType::River))
		{
			head = DevelopRiver(route, head);
		}

		//�J�񂪏I�������ʒu����ċA�I�ɊJ��
		auto nextHead = std::find_if(head, route.end(), [](auto&& place)
		{
			//�삶��Ȃ��A���A������Ȃ��^�C�v��T��
			//NOTE:�u�R����Ȃ��v���܂߂�ƁA��Ɨאڂ����R���J��ł��Ȃ��̂ŏ����Ɋ܂߂Ȃ�
			return !place->IsType(PlaceType::River) && !place->IsType(PlaceType::Bridge);
		});

		DevelopPlace(route, nextHead);
	}

	/**************************************
	�R�̊J������
	***************************************/
	PlaceIterator FieldController::FieldDevelopper::DevelopMountain(PlaceVector & route, PlaceIterator mountain)
	{
		using namespace Field::Model;

		//�Ώۂ̃v���C�X�̑O�ɂ���R�ȊO�̃v���C�X��T��
		auto start = std::find_if(ReversePlaceIterator(mountain), route.rend(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//�R�ȊO��������Ȃ������ꍇ�͑������^�[��
		if (start == route.rend())
		{
			return route.end();
		}

		//�Ώۂ̃v���C�X�̌��ɂ���R�A��ȊO�̃v���C�X��T��
		auto end = std::find_if(mountain, route.end(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//�R�ȊO��������Ȃ��������A��̏ꍇ�͑������^�[��
		if (end == route.end())
		{
			return route.end();
		}

		//start��end�����ԃv���C�X�̃R���e�i���쐬
		PlaceVector container;
		container.assign(start.base(), end);

		//�X�g�b�N������Ă���ΊJ��
		int cntMountain = container.size();
		if (cntMountain <= entity->stockDevelopMountain)
		{
			for (auto&& place : container)
			{
				place->SetType(PlaceType::None);
			}

			entity->stockDevelopMountain -= cntMountain;
		}
		else
		{
			//�G���[���b�Z�[�W���Đ�
		}

		return end + 1;
	}

	/**************************************
	��̊J������
	***************************************/
	PlaceIterator FieldController::FieldDevelopper::DevelopRiver(PlaceVector & route, PlaceIterator river)
	{
		using namespace Field::Model;

		//��̈�O�̃v���C�X�i�n�_�j���ǂ̕����ŗאڂ��Ă��邩�m�F
		PlaceModel* start = *(river - 1);
		Adjacency startAdjacency = (*river)->IsAdjacent(start);

		//�v���C�X��O�ֈ���m�F���Ă����I�_��T��
		PlaceIterator end = route.end();
		for (auto itr = river + 1; itr != route.end(); itr++)
		{
			PlaceModel* prev = *(itr - 1);
			PlaceModel* place = *itr;
			Adjacency adjacency = place->IsAdjacent(prev);

			//�אڕ����������ɂȂ��Ă��Ȃ���Α������^�[��
			if (adjacency != startAdjacency)
				return itr;

			//�R���o�Ă����瑁�����^�[��
			if (place->IsType(PlaceType::Mountain))
				return itr;

			//���̏ꍇ�́A�A���ł��Ȃ������ł���Α������^�[��
			if (place->IsType(PlaceType::Bridge))
			{
				std::vector<Adjacency> direction = place->GetConnectingAdjacency();

				if (!Utility::IsContain(direction, adjacency))
				{
					return itr;
				}
			}

			//�����˂�����^�C�v�ł���΃u���[�N
			if (!place->IsDevelopableType())
			{
				end = itr;
				break;
			}
		}

		//�I�_��������Ȃ������̂ő������^�[��
		if (end == route.end())
			return route.end();

		//�n�_�ƏI�_�̊Ԃ̐�R���e�i���쐬
		PlaceVector riverVector;
		riverVector.assign(river, end);

		//�X�g�b�N������Ă���ΊJ��
		int cntRiver = riverVector.size();
		if (cntRiver <= entity->stockDevelopRiver)
		{
			Adjacency inverseStartAdjacency = GetInverseSide(startAdjacency);
			for (auto&& river : riverVector)
			{
				river->SetType(PlaceType::Bridge);
				river->AddDirection(startAdjacency);
				river->AddDirection(inverseStartAdjacency);

				entity->placeActController->SetActor(river);
			}

			entity->stockDevelopRiver -= cntRiver;
		}
		else
		{
			//�G���[���b�Z�[�W�̍Đ�
		}

		return end;
	}

}