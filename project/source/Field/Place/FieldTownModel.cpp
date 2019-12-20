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
	TownModel::TownModel(
		const PlaceModel* place, 
		std::function<void(const PlaceModel *start, const PlaceModel *goal, const PlaceModel* town)>& departAction,
		std::function<void(const PlaceModel *place, int current, int next)> &morphAction) :
		uniqueID(incrementID++),
		place(place),
		linkLevel(0),
		biasLinkLevel(0),
		cntFrame(0),
		levelMorphing(0),
		indexDestination(0),
		departPassenger(departAction),
		startMorph(morphAction)
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
			departPassenger(linkedTown[indexDestination].second, linkedTown[indexDestination].first, place);
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
	�����N���x���擾����
	***************************************/
	int TownModel::LinkLevel()
	{
		//�����N���x����0�ȉ��ɂ͂��Ȃ�
		return Math::Max(1, linkLevel + biasLinkLevel);
	}

	/**************************************
	�␳�l�Ȃ��̃����N���x���擾����
	***************************************/
	int TownModel::PureLinkLevel() const
	{
		return linkLevel;
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

		int currentLevel = linkLevel + biasLinkLevel;

		//5�ȏ�ɂȂ����Ƃ���Ƀ��[�t�B���O
		if (levelMorphing < 2 && currentLevel >= 5)
		{
			startMorph(place, levelMorphing, 2);
			levelMorphing = 2;
		}
		//0����オ�����Ƃ����Ƀ��[�t�B���O
		else if (levelMorphing < 1 && currentLevel >= 1)
		{
			startMorph(place, levelMorphing, 1);
			levelMorphing = 1;
		}
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
		return { pos, LinkLevel() };
	}
}