//=====================================
//
//FieldJunctionModel.cpp
//�@�\:�����_�̃��W�b�N���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldJunctionModel.h"
#include "FieldPlaceModel.h"
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
		place(place)
	{

	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	JunctionModel::~JunctionModel()
	{
	}

	/**************************************
	���G�x�擾����
	***************************************/
	float JunctionModel::TrafficJam()
	{
		RouteContainer container = place->GetConnectingRoutes();

		//���g�ɗ������Ă���l�����m�F
		float inflowNum = 0.0f;
		for (auto&& route : container)
		{

		}

		return inflowNum;
	}

}