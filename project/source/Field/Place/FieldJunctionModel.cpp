//=====================================
//
//FieldJunctionModel.cpp
//�@�\:�����_�̃��W�b�N���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldJunctionModel.h"
#include "FieldPlaceModel.h"
#include "FieldTownModel.h"
#include "../Route/RouteModel.h"

namespace Field::Model
{
	/**************************************
	static�����o
	***************************************/
	unsigned JunctionModel::incrementID = 0;

	/**************************************
	�R���X�g���N�^
	***************************************/
	JunctionModel::JunctionModel(const PlaceModel * place) :
		uniqueID(incrementID++),
		place(place),
		trafficJam(0.0f)
	{

	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	JunctionModel::~JunctionModel()
	{
	}

	/**************************************
	���G�x�v�Z����
	***************************************/
	void JunctionModel::Calculate(TownContainer & townContainer)
	{
		RouteContainer container = place->GetConnectingRoutes();

		//���g�ɗ������Ă���l�����m�F
		float inflowNum = 0.0f;
		for (auto&& route : container)
		{
			PlaceModel* opponent = route->GetOtherEdge(place);

			if (!opponent->IsType(PlaceType::Town))
				continue;

			inflowNum += townContainer[opponent->ID()]->DepatureNum();
		}

		trafficJam = inflowNum;
	}

	/**************************************
	���G�x�擾����
	***************************************/
	float JunctionModel::TrafficJam(TownContainer& townContainer)
	{
		return trafficJam;
	}

}