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
#include <algorithm>

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
	TownModel::TownModel(const PlaceModel* place, std::function<void(const PlaceModel *start, const PlaceModel *goal, const PlaceModel* town)> *action) :
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
		if (linkedTown.size() == 0)
			return;

		//4�b�����Ɍq�����Ă���X�Ɍ������ăp�b�Z���W���[���o��������
		const int Interval = 120;
		if (cntFrame % Interval == 0)
		{
			indexDestination = Math::WrapAround(0, (int)linkedTown.size(), ++indexDestination);
			(*departPassenger)(linkedTown[indexDestination].second, linkedTown[indexDestination].first, place);
		}

		cntFrame++;
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
		return linkLevel + biasLinkLevel;
	}

	/**************************************
	���W�x�擾����
	***************************************/
	float TownModel::DevelopmentLevel()
	{
		return developmentLevel;
	}

	/**************************************
	�q�����Ă���X��T������
	***************************************/
	void TownModel::FindLinkedTown()
	{
		linkLevel = 0;

		std::vector<unsigned> searchedRoute;

		linkedTown.clear();
		for(indexSearchingGate = 0; indexSearchingGate < gateList.size(); indexSearchingGate++)
		{
			auto routeList = gateList[indexSearchingGate]->GetConnectingRoutes();
			searchedRoute.clear();
			for (auto&& route : routeList)
			{
				route->FindLinkedTown(this, searchedRoute);
			}
		}

		developmentLevel = (float)linkLevel;
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
		//��������ɃJ�E���g�ς݂��ǂ�������
		bool searchedTown = false;
		bool linkedSameRoute = false;

		for (auto&& route : linkedTown)
		{
			searchedTown |= route.first == place;
			linkedSameRoute |= searchedTown && (route.second == gateList[indexSearchingGate]);
		}

		//�����X���q�����Ă��Ȃ���΃����N���x���𑝉�
		if (!searchedTown)
			linkLevel++;

		//�������[�g���Ȃ���Βǉ�
		if (!linkedSameRoute)
			linkedTown.push_back(std::make_pair(place, gateList[indexSearchingGate]));
	}

	//=================================
	// ���擾����
	//=================================
	PlaceData TownModel::GetPlaceData()
	{
		FieldPosition pos = place->GetPosition();
		return { pos, (int)developmentLevel };
	}
}