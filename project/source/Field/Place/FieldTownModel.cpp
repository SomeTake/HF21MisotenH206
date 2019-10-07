//=====================================
//
//FieldTownModel.cpp
//�@�\:�X�̃��W�b�N���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldTownModel.h"
#include "FieldPlaceModel.h"

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
	TownModel::TownModel(PlaceModel * place) :
		uniqueID(incrementID++),
		place(place),
		cntGate(0)
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
}