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
#include "../Place/FieldPlaceContainer.h"
#include "../../FieldObject/InfoController.h"
#include "../../Viewer/GameScene/Controller/FieldViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../Reward/RewardController.h"
#include "../../Sound/SoundConfig.h"
#include "../../../Framework/Sound/SoundEffect.h"

#include "../../../Library/cppLinq/cpplinq.hpp"

#include <algorithm>

namespace Field
{
	/**************************************
	static�����o
	***************************************/
	const int FieldController::FieldDevelopper::MaxStock = 99;
	const int FieldController::FieldDevelopper::InitStock = 20;

	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldController::FieldDevelopper::FieldDevelopper(FieldController * controller) :
		entity(controller),
		stockNum(InitStock)
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
		using cpplinq::from;
		using cpplinq::intersect_with;
		using cpplinq::union_with;
		using cpplinq::except;
		using cpplinq::count;

		std::vector<PlaceModel*> route = entity->operateContainer->GetPlaces();
	
		if (route.size() > 1)
		{
			//���[���ʂ�Place�Ŗ�����Α������^�[��
			auto firstEdge = route.front()->GetEdgeOpponents();
			auto lastEdge = route.back()->GetEdgeOpponents();
			auto first = from(firstEdge);							//�n�_���̘A������
			auto last = from(lastEdge);								//�I�_���̘A������
			auto intersectList = first >> intersect_with(last);		//�A������̐ϏW��
			auto unionList = first >> union_with(last);				//�A������̘a�W��

			//�a�W������ϏW����������XOR�����߂�
			//XOR�̐���0�Ȃ烋�[�g�����[�v���Ă���̂Ń��^�[��
			if (unionList >> except(intersectList) >> count() == 0)
				return;
		}

		int cntRoot = 0;
		//����Ώۂ̃v���C�X��Road�^�C�v�ɕϊ�
		for (auto&& place : route)
		{
			if (place->IsType(PlaceType::None))
				place->SetType(PlaceType::Road);

			cntRoot++;
		}

		//���[�g���f���쐬
		RouteModelPtr ptr = RouteModel::Create(entity->onConnectTown, route);

		//�[�_�ݒ�
		ptr->SetEdge();

		//�אڂ��郋�[�g�ƘA��������
		entity->routeProcessor->ConnectWithEdge(ptr, entity->routeContainer);
		entity->routeProcessor->Process(ptr, entity->routeContainer);

		//�A�N�^�[����
		entity->placeActController->SetActor(ptr);

		//�����N���x�����v�Z
		int prevLinkLevel = entity->placeContainer->GetPureLinkLevel();
		entity->placeContainer->CalcLinkLevel();

		//�������������N���x����\��
		int currentLinkLevel = entity->placeContainer->GetPureLinkLevel();
		int diff = currentLinkLevel - prevLinkLevel;
		if (diff > 0)
		{
			SE::Play(SoundConfig::SEID::LinkLevelUpSE, 1.0f);
			entity->flgWaitPopup = true;
			entity->viewer->ViewLinkLevelUp(diff, [&]()
			{
				entity->flgWaitPopup = false;
			});

			GameParticleManager::Instance()->Generate(GameParticle::LinkLevelUp, { SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
		}

		// �ڑ�����Ă���S�Ă̒��̃����N���x�����Z�b�g
		entity->SetLinkLevelInfo();

		//�R�[���o�b�N
		entity->onBuildRoad(route);

		// �����[�h�ɔ��f
		RewardController::Instance()->SetRewardData(RC::Type::Pioneer, cntRoot);
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
		if (cntMountain <= stockNum)
		{
			for (auto&& place : container)
			{
				place->SetType(PlaceType::None);
				entity->placeActController->DestroyActor(place);
			}

			stockNum -= cntMountain;

			// �����[�h�ɔ��f
			RewardController::Instance()->SetRewardData(RC::Type::Destructer, cntMountain);

			//SE�Đ�
			SE::Play(SoundConfig::SEID::Bom, 1.0f);
		}
		else
		{
			//�G���[���b�Z�[�W���Đ�
			entity->viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::StockShortage);
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

		//��̈�O�����Ȃ炻�������˂����Ȃ�
		if (start->IsType(PlaceType::Bridge))
			return route.end();

		//�v���C�X��O�ֈ���m�F���Ă����I�_��T��
		PlaceIterator end = route.end();
		for (auto itr = river + 1; itr != route.end(); itr++)
		{
			PlaceModel* prev = *(itr - 1);
			PlaceModel* place = *itr;
			Adjacency adjacency = place->IsAdjacent(prev);

			//�אڕ����������ɂȂ��Ă��Ȃ���Α������^�[��
			if (adjacency != startAdjacency)
			{
				entity->viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::CurveBridge);
				return itr;
			}

			//�R���o�Ă����瑁�����^�[��
			if (place->IsType(PlaceType::Mountain))
				return itr;

			//���̏ꍇ�́A�A���ł��Ȃ������ł���Α������^�[��
			if (place->IsType(PlaceType::Bridge))
			{
				std::vector<Adjacency> direction = place->GetConnectingAdjacency();

				if (!Utility::IsContain(direction, adjacency))
				{
					//�G���[���b�Z�[�W��\��
					entity->viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::BridgeConnection);
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
		if (cntRiver <= stockNum)
		{
			Adjacency inverseStartAdjacency = GetInverseSide(startAdjacency);
			for (auto&& river : riverVector)
			{
				river->SetType(PlaceType::Bridge);
				river->AddDirection(startAdjacency);
				river->AddDirection(inverseStartAdjacency);

				entity->placeActController->SetActor(river);
			}

			stockNum -= cntRiver;

			// �����[�h�ɔ��f
			RewardController::Instance()->SetRewardData(RC::Type::Artist, cntRiver);

			//SE�Đ�
			SE::Play(SoundConfig::Fall, 1.0f);
		}
		else
		{
			//�G���[���b�Z�[�W���Đ�
			entity->viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::StockShortage);
		}

		return end;
	}

	/**************************************
	�X�g�b�N���Z����
	***************************************/
	void FieldController::FieldDevelopper::AddStock(int num)
	{
		stockNum = Math::Min(MaxStock, stockNum + num);
	}

	/**************************************
	�X�g�b�N���̃��Z�b�g
	***************************************/
	void Field::FieldController::FieldDevelopper::ResetStock(void)
	{
		stockNum = InitStock;
	}

	/**************************************
	�X�g�b�N�����ߍ��ݏ���
	***************************************/
	void FieldController::FieldDevelopper::EmbedViewerParam(GameViewerParam & param)
	{
		param.stockNum = stockNum;
	}
}