//=====================================
//
//FieldPlaceModel.cpp
//�@�\:�t�B�[���h��̃v���C�X���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldPlaceModel.h"

#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../../Library/cppLinq/cpplinq.hpp"
#include "../Route/RouteProcessor.h"
#include "../../FieldObject/Actor/StraightRoadActor.h"

#include <algorithm>

/**************************************
�O���[�o���ϐ�
***************************************/
#ifdef DEBUG_PLACEMODEL
static const char* PolygonName[] =
{
	"None",
	"Road",
	"Town",
	"River",
	"Bridge",
	"Junction",
	"Mountain",
};

#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#endif

namespace Field::Model
{
	/**************************************
	cpplinq��using�錾
	***************************************/
	using cpplinq::from;
	using cpplinq::union_with;
	using cpplinq::to_vector;
	using cpplinq::intersect_with;
	using cpplinq::except;
	using cpplinq::count;

	/**************************************
	static�����o
	***************************************/
	unsigned PlaceModel::incrementID = 0;

	/**************************************
	�R���X�g���N�^
	***************************************/
	PlaceModel::PlaceModel(PlaceType type, int x, int z) :
		uniqueID(incrementID++),
		type(type),
		prevType(type),
		Position(x, z)
	{
		//�אڃv���C�X�̃R���e�i������
		adjacencies.resize(Adjacency::Max, NULL);

		connectDirection.reserve(Adjacency::Max);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	PlaceModel::~PlaceModel()
	{
		belongRouteList.clear();
	}

#ifdef DEBUG_PLACEMODEL
	/**************************************
	�`�揈��
	***************************************/
	void PlaceModel::DrawDebug()
	{
		if (type != PlaceType::River && type != PlaceType::Town)
			return;

		//�e�X�g�`��
		Transform transform = Transform(
			Position.ConvertToWorldPosition() + Vector3::Up,
			{ D3DXToRadian(90.0f), 0.0f, 0.0f },
			Vector3::One);
		transform.SetWorld();
		BoardPolygon *polygon;
		ResourceManager::Instance()->GetPolygon(PolygonName[type], polygon);
		polygon->Draw();
	}
#endif

	/**************************************
	���W�擾����
	***************************************/
	FieldPosition PlaceModel::GetPosition() const
	{
		return Position;
	}

	/**************************************
	ID�擾����
	***************************************/
	unsigned PlaceModel::ID() const
	{
		return uniqueID;
	}

	/**************************************
	�אڃv���C�X�ǉ�
	***************************************/
	void PlaceModel::AddAdjacency(PlaceModel *adjacency, Adjacency type)
	{
		adjacencies[type] = adjacency;
	}

	/**************************************
	���[�g���n�߂��邩
	***************************************/
	bool PlaceModel::CanStartRoute() const
	{
		//�󔒃^�C�v�����łȂ���Γ��ɏo���Ȃ�
		if (type != PlaceType::None && type != PlaceType::Bridge)
			return false;

		//�אڃv���C�X�Ɍ����_�A�X�A�����܂܂�Ă����烋�[�g���n�߂���
		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			if (!adjacency->IsConnectableType())
				continue;

			//���^�C�v�̏ꍇ�A�אڕ������m�F
			if (type == PlaceType::Bridge)
			{
				Adjacency adjacenctType = IsAdjacent(adjacency);
				if (Utility::IsContain(connectDirection, adjacenctType))
					return true;
			}
			//�󔒃^�C�v�Ȃ疳������true
			else
			{
				return true;
			}
		}

		return false;
	}

	/**************************************
	���ɕς����邩
	***************************************/
	bool PlaceModel::ChangeableRoad(Adjacency prev) const
	{
		//None�Ƌ��̂ݓ��ɂ��邱�Ƃ��o����
		if (type == PlaceType::None)
			return true;

		//���̏ꍇ�͕������l��
		if (type == PlaceType::Bridge)
		{
			if (Utility::IsContain(connectDirection, prev))
				return true;
			else
				return false;
		}

		return false;
	}

	/**************************************
	�J��\�ȃ^�C�v��
	***************************************/
	bool PlaceModel::IsDevelopableType() const
	{
		if (type == PlaceType::River)
			return true;

		if (type == PlaceType::Mountain)
			return true;

		return false;
	}

	/**************************************
	�v���C�X�Ɨאڂ��Ă��邩
	***************************************/
	Adjacency PlaceModel::IsAdjacent(const PlaceModel * place) const
	{
		//�אڃv���C�X�̒����瓙�������̂�����
		auto itr = std::find_if(adjacencies.begin(), adjacencies.end(), [&](auto adjacency)
		{
			return adjacency == place;
		});

		if (itr == adjacencies.end())
			return Adjacency::NotAdjacenct;

		return (Adjacency)std::distance(adjacencies.begin(), itr);
	}

	/**************************************
	�A���\�ȃ^�C�v��
	***************************************/
	bool PlaceModel::IsConnectableType() const
	{
		if (type == PlaceType::Road)
			return true;

		if (type == PlaceType::Junction)
			return true;

		if (type == PlaceType::Town)
			return true;

		return false;
	}

	/**************************************
	�������[�g�ɑ����Ă��邩
	***************************************/
	bool PlaceModel::IsSameRoute(PlaceModel * place) const
	{
		//����Ǝ����̏������X�g�̐ϏW�������߂�
		auto intersect = from(belongRouteList)
			>> intersect_with(from(place->belongRouteList))
			>> to_vector();

		//�ϏW������łȂ���Γ������[�g�ɑ����Ă���
		return !intersect.empty();
	}

	/**************************************
	�A������̎擾
	TODO:�A������𕡐���
	***************************************/
	PlaceModel* PlaceModel::GetConnectTarget() const
	{
		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			//�A���s�ł����continue
			if (!adjacency->IsConnectableType())
				continue;

			//�A���\�ł����Ă�Town�͕s��
			if (adjacency->IsType(PlaceType::Town))
				continue;

			//�������[�g�ɑ����Ă��Ȃ���ΘA���ł���
			if (!IsSameRoute(adjacency))
				return adjacency;
		}

		return nullptr;
	}

	/**************************************
	�[�_�ƂȂ�v���C�X�̎擾
	***************************************/
	PlaceModel* PlaceModel::GetEdgeOpponent() const
	{
		PlaceModel* opponent = nullptr;

		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			//�X���ŗD��Œ[�_�Ƃ���
			if (adjacency->IsType(PlaceType::Town))
				return adjacency;

			//�X�������_�Ȃ�[�_�Ƃ��Đ���
			if (adjacency->IsType(PlaceType::Junction))
				opponent = adjacency;

			//���œ������[�g�ɑ����Ă��Ȃ���Β[�_�Ƃ��Đ���
			if (adjacency->IsType(PlaceType::Road) && !IsSameRoute(adjacency))
				opponent = adjacency;
		}

		return opponent;
	}

	/**************************************
	���[�g���f���ւ̏���
	***************************************/
	void PlaceModel::BelongRoute(std::shared_ptr<RouteModel> route)
	{
		//�d���m�F
		auto itr = std::find(belongRouteList.begin(), belongRouteList.end(), route);
		if (itr == belongRouteList.end())
		{
			belongRouteList.push_back(std::shared_ptr<RouteModel>(route));
		}
	}

	/**************************************
	���[�g���f���ւ̏���
	***************************************/
	void PlaceModel::BelongRoute(std::vector<std::shared_ptr<RouteModel>>& routes)
	{
		//�d���m�F(���g�̏������X�g�Ƃ̍��W�������߂�)
		auto exceptRoute = from(routes)
			>> except(from(belongRouteList))
			>> to_vector();

		//���W���̃R���e�i���������X�g�̖����ɃR�s�[���Ēǉ�
		if (!exceptRoute.empty())
			std::copy(exceptRoute.begin(), exceptRoute.end(), std::back_inserter(belongRouteList));
	}

	/**************************************
	���[�g���f�����痣�E
	***************************************/
	void PlaceModel::ExitRoute(std::shared_ptr<RouteModel> route)
	{
		auto itr = std::remove(belongRouteList.begin(), belongRouteList.end(), route);
		belongRouteList.erase(itr, belongRouteList.end());
	}

	/**************************************
	�^�C�v����
	***************************************/
	bool PlaceModel::IsType(PlaceType type) const
	{
		return this->type == type;
	}

	/**************************************
	�^�C�v�Z�b�g
	***************************************/
	void PlaceModel::SetType(PlaceType type)
	{
		prevType = this->type;
		this->type = type;
	}

	/**************************************
	�^�C�v�擾
	***************************************/
	const PlaceType PlaceModel::GetType() const
	{
		return type;
	}

	/**************************************
	�ȑO�̃^�C�v�擾
	***************************************/
	const PlaceType PlaceModel::GetPrevType() const
	{
		return prevType;
	}

	/**************************************
	���[�g�擾
	***************************************/
	RouteModelPtr PlaceModel::GetConnectingRoute() const
	{
		return *(belongRouteList.begin());
	}

	/**************************************
	�^�C�v�Z�b�g
	***************************************/
	RouteContainer PlaceModel::GetConnectingRoutes() const
	{
		return belongRouteList;
	}

	/**************************************
	�����Z�b�g����
	***************************************/
	void PlaceModel::AddDirection(Adjacency direction)
	{
		if (direction == Adjacency::NotAdjacenct)
			return;

		auto itr = std::find(connectDirection.begin(), connectDirection.end(), direction);
		if (itr == connectDirection.end())
			connectDirection.push_back(direction);
	}

	/**************************************
	�����Z�b�g����
	***************************************/
	void PlaceModel::AddDirection(PlaceModel* place)
	{
		Adjacency adjacencyType = IsAdjacent(place);

		AddDirection(adjacencyType);
	}

	/**************************************
	�A�������擾����
	***************************************/
	std::vector<Adjacency> PlaceModel::GetConnectingAdjacency() const
	{
		return connectDirection;
	}

}