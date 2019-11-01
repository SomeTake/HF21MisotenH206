//=====================================
//
//FieldTownModel.cpp
//�@�\:�X�̃��W�b�N���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldTownModel.h"
#include "FieldPlaceModel.h"
#include "../Route/RouteModel.h"

namespace Field::Model
{
	/**************************************
	static�����o
	***************************************/
	unsigned TownModel::incrementID = 0;
	const float TownModel::BaseDepatureNum = 100.0f;

	/**************************************
	�R���X�g���N�^
	***************************************/
	TownModel::TownModel(const PlaceModel* place, std::function<void(const PlaceModel *start, const PlaceModel *goal)> *action) :
		uniqueID(incrementID++),
		place(place),
		linkLevel(0),
		developmentLevel(0),
		biasLinkLevel(0),
		cntFrame(0),
		indexDestination(0),
		departPassenger(action)
	{
		gateList.reserve(4);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	TownModel::~TownModel()
	{
	}

	/**************************************
	�X�V����
	***************************************/
	void TownModel::Update()
	{
		cntFrame++;
		
		if (linkedTown.size() == 0)
			return;

		//4�b�����Ɍq�����Ă���X�Ɍ������ăp�b�Z���W���[���o��������
		if (cntFrame % 30 == 0)
		{
			indexDestination = Math::WrapAround(0, (int)linkedTown.size(), ++indexDestination);
			(*departPassenger)(place, linkedTown[indexDestination]);
		}
	}

	/**************************************
	�Q�[�g�ǉ�����
	***************************************/
	void TownModel::AddGate(const PlaceModel* gate)
	{
		auto itr = std::find(gateList.begin(), gateList.end(), gate);

		if (itr == gateList.end())
		{
			gateList.push_back(gate);
		}
	}

	/**************************************
	�o���l���擾����
	***************************************/
	float TownModel::DepatureNum()
	{
		return 100.0f / gateList.size();
	}

	/**************************************
	�Q�[�g���擾����
	***************************************/
	int TownModel::GateNum()
	{
		return gateList.size();
	}

	/**************************************
	�����N���x���擾����
	***************************************/
	int TownModel::LinkLevel()
	{
		return linkLevel;
	}

	/**************************************
	���W�x�擾����
	***************************************/
	float TownModel::DevelopmentLevel()
	{
		return developmentLevel;
	}

	/**************************************
	�������鎞�ɌĂ΂�鏈��
	***************************************/
	void TownModel::FindLinkedTown()
	{
		linkLevel = biasLinkLevel;

		RouteContainer searchedRoute;
		std::vector<const PlaceModel*> searchedTown;
		searchedTown.push_back(place);

		RouteContainer belongRoute = place->GetConnectingRoutes();

		RoutePlaceStack routeStack;

		linkedTown.clear();
		for (auto&& route : belongRoute)
		{
			linkLevel += route->FindLinkedTown(this, searchedRoute, searchedTown, routeStack, place);
		}

		developmentLevel = (float)linkLevel /** linkLevel*/;
	}

	/**************************************
	�����N���x�����Z����
	***************************************/
	void TownModel::AddLinkLevel(int num)
	{
		biasLinkLevel += num;
	}

	/**************************************
	PlaceModel�擾����
	***************************************/
	const PlaceModel * TownModel::GetPlace()
	{
		return place;
	}

	/**************************************
	�o�H�ǉ�����
	***************************************/
	void TownModel::AddLinkedTown(const PlaceModel *place)
	{
		linkedTown.push_back(place);
	}
}