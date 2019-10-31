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
	TownModel::TownModel(const PlaceModel * place, std::function<void(std::vector<D3DXVECTOR3>&)> *action) :
		uniqueID(incrementID++),
		place(place),
		cntGate(0),
		linkLevel(0),
		developmentLevel(0),
		biasLinkLevel(0),
		cntFrame(0),
		indexDestination(0),
		departPassenger(action)
	{

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

		if (routeContainer.size() == 0)
			return;

		//4�b�����Ɍq�����Ă���X�Ɍ������ăp�b�Z���W���[���o��������
		if (cntFrame % 120 == 0)
		{
			indexDestination = Math::WrapAround(0, (int)routeContainer.size(), ++indexDestination);
			(*departPassenger)(routeContainer[indexDestination]);
		}
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
		std::vector<const PlaceModel*> searchedTown;
		searchedTown.push_back(place);

		RouteContainer belongRoute = place->GetConnectingRoutes();

		RoutePlaceStack routeStack;

		routeContainer.clear();
		for (auto&& route : belongRoute)
		{
			linkLevel += route->FindLinkedTown(this, searchedRoute, searchedTown, routeStack, place);
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

	/**************************************
	�o�H�ǉ�����
	***************************************/
	void TownModel::AddLinkedRoute(std::vector<D3DXVECTOR3>& route)
	{
		//�R�s�[���ďd�����폜
		std::vector<D3DXVECTOR3> container(route);
		auto itr = std::unique(container.begin(), container.end());
		container.erase(itr, container.end());

		bool shouldAdd = true;

		//�ړI�n���������[�g�����ɂ���ꍇ�͒������r
		for (auto&& route : routeContainer)
		{
			if (route.back() != container.back())
				continue;

			if (route.size() > container.size())
			{
				route = container;
			}

			shouldAdd = false;
		}

		if(shouldAdd)
			routeContainer.push_back(container);
	}
}