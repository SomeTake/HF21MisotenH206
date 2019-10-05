//=====================================
//
//FieldPlaceModel.cpp
//�@�\:�t�B�[���h��̃v���C�X���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldPlaceModel.h"

#include "../../FieldObject/PlaceActor.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

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
		Position(x, z),
		actor(nullptr)
	{
		//�אڃv���C�X�̃R���e�i������
		adjacencies.resize(Adjacency::Max, NULL);

		//�A�N�^�[�̐���
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	PlaceModel::~PlaceModel()
	{
		belongRouteList.clear();
		SAFE_DELETE(actor);
	}

	/**************************************
	�X�V����
	***************************************/
	void PlaceModel::Update()
	{
		if (actor != NULL)
		{
			actor->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void PlaceModel::Draw()
	{
		if (actor != NULL)
		{
			actor->Draw();
		}

#ifdef DEBUG_PLACEMODEL
		//�e�X�g�`��
		Transform transform = Transform(
			{ Position.x * 10.0f, 1.0f, Position.z * 10.0f },
			{ D3DXToRadian(90.0f), 0.0f, 0.0f },
			Vector3::One);
		transform.SetWorld();
		BoardPolygon *polygon;
		ResourceManager::Instance()->GetPolygon(PolygonName[type], polygon);
		polygon->Draw();
#endif
	}

	/**************************************
	���W�擾����
	***************************************/
	FieldPosition PlaceModel::GetPosition() const
	{
		return Position;
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
	bool PlaceModel::CanStartRoute()
	{
		//�󔒃^�C�v�����łȂ���Γ��ɏo���Ȃ�
		if(!ChangeableRoad())
			return false;

		//�אڃv���C�X�Ɍ����_�A�X�A�����܂܂�Ă����烋�[�g���n�߂���
		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			if (adjacency->IsConnectableType())
				return true;
		}

		return false;
	}

	/**************************************
	���ɕς����邩
	***************************************/
	bool PlaceModel::ChangeableRoad()
	{
		//None�Ƌ��̂ݓ��ɂ��邱�Ƃ��o����
		if (type == PlaceType::None)
			return true;

		if (type == PlaceType::Bridge)
			return true;

		return false;
	}

	/**************************************
	�v���C�X�Ɨאڂ��Ă��邩
	***************************************/
	bool PlaceModel::IsAdjacent(PlaceModel * place)
	{
		//�אڃv���C�X�̒����瓙�������̂�����
		auto itr = std::find_if(adjacencies.begin(), adjacencies.end(), [&](auto adjacency)
		{
			return adjacency == place;
		});

		return itr != adjacencies.end();
	}

	/**************************************
	�A���\�ȃ^�C�v��
	***************************************/
	bool PlaceModel::IsConnectableType()
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
	bool PlaceModel::IsSameRoute(PlaceModel * place)
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
	PlaceModel* PlaceModel::GetConnectTarget()
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
	PlaceModel* PlaceModel::GetEdgeOpponent()
	{
		for (auto&& adjacency : adjacencies)
		{
			if (adjacency == NULL)
				continue;

			//���œ������[�g�ɑ����Ă��Ȃ���Β[�_�Ƃ��Đ���
			if (adjacency->IsType(PlaceType::Road) && !IsSameRoute(adjacency))
				return adjacency;

			//�X�������_�Ȃ�[�_�Ƃ��Đ���
			if (adjacency->IsType(PlaceType::Town) || adjacency->IsType(PlaceType::Junction))
				return adjacency;
		}
		return nullptr;
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
		if(!exceptRoute.empty())
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
	bool PlaceModel::IsType(PlaceType type)
	{
		return this->type == type;
	}

	/**************************************
	�^�C�v�Z�b�g
	***************************************/
	void PlaceModel::SetType(PlaceType type)
	{
		this->type = type;
	}

	/**************************************
	���[�g�擾
	***************************************/
	RouteModelPtr PlaceModel::GetConnectingRoute()
	{
		return *(belongRouteList.begin());
	}

	/**************************************
	�^�C�v�Z�b�g
	***************************************/
	RouteContainer PlaceModel::GetConnectingRoutes()
	{
		return belongRouteList;
	}
}