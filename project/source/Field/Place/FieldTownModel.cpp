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
	TownModel::TownModel(const PlaceModel * place) :
		uniqueID(incrementID++),
		place(place),
		cntGate(0),
		linkLevel(0),
		developmentLevel(0),
		biasLinkLevel(0)
	{

	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	TownModel::~TownModel()
	{
	}

	/**************************************
	�Q�[�g�ǉ�����
	***************************************/
	void TownModel::AddGate()
	{
		cntGate++;
	}

	/**************************************
	�o���l���擾����
	***************************************/
	float TownModel::DepatureNum()
	{
		return 100.0f / cntGate;
	}

	/**************************************
	�Q�[�g���擾����
	***************************************/
	int TownModel::GateNum()
	{
		return cntGate;
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
		std::vector<PlaceModel*> searchedTown;

		RouteContainer belongRoute = place->GetConnectingRoutes();
		for (auto&& route : belongRoute)
		{
			linkLevel += route->FindLinkedTown(place, searchedRoute, searchedTown);
		}

		developmentLevel = (float)linkLevel * linkLevel;
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
}