//=====================================
//
//FieldPlaceModel.h
//�@�\:�t�B�[���h��̃v���C�X���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDPLACEMODEL_H_
#define _FIELDPLACEMODEL_H_

#include "../../../main.h"
#include "../FieldConfig.h"
#include "PlaceConfig.h"

#include <vector>

/**************************************
�}�N����`
***************************************/

/**************************************
�O���錾
***************************************/
class PlaceActor;

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class RouteModel;

	/**************************************
	�N���X��`
	***************************************/
	class PlaceModel
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		PlaceModel(PlaceType type, int x, int z);
		~PlaceModel();

		//���W�擾
		FieldPosition GetPosition() const;

		//ID�擾
		unsigned ID() const;

		//�אڃv���C�X�̒ǉ�
		void AddAdjacency(PlaceModel *adjacency, Adjacency type);
	
		//���[�g���n�߂��邩
		bool CanStartRoute() const;

		//���ɕς����邩
		bool ChangeableRoad(Adjacency prev) const;

		//�J��\�ȃ^�C�v��
		bool IsDevelopableType() const;

		//place�Ɨאڂ��Ă��邩
		Adjacency IsAdjacent(const PlaceModel* place) const;

		//�A���ł���^�C�v��
		bool IsConnectableType() const;

		//�������[�g�ɑ����Ă��邩
		bool IsSameRoute(PlaceModel* place) const;

		//�A���Ώۂ̎擾
		PlaceModel* GetConnectTarget() const;		//TODO:�A���Ώۂ̕�����

		//�[�_�ƂȂ�Place�̎擾
		PlaceModel* GetEdgeOpponent()  const;
		std::vector<PlaceModel*> GetEdgeOpponents() const;

		//���[�g���f���ւ̏����A���E
		void BelongRoute(std::shared_ptr<RouteModel> route);
		void BelongRoute(std::vector<std::shared_ptr<RouteModel>>& routes);
		void ExitRoute(std::shared_ptr<RouteModel> route);

		//�^�C�v����A�ύX����
		bool IsType(PlaceType type) const;
		void SetType(PlaceType type);
		const PlaceType GetType() const;
		const PlaceType GetPrevType() const;

		//�������[�g�擾
		RouteModelPtr GetConnectingRoute() const;
		RouteContainer GetConnectingRoutes() const;

		//�������菈���A�擾����
		void AddDirection(Adjacency direction);
		void AddDirection(PlaceModel* place);
		std::vector<Adjacency> GetConnectingAdjacency() const;

#ifdef DEBUG_PLACEMODEL
		//�f�o�b�O�p�`�揈��
		void DrawDebug();
#endif

	private:
		//ID
		static unsigned incrementID;
		unsigned uniqueID;

		//�^�C�v
		PlaceType type, prevType;

		//���W
		const FieldPosition Position;

		//�������Ă��郋�[�g�̎Q�ƃR���e�i
		std::vector<std::shared_ptr<RouteModel>> belongRouteList;

		//�אڃv���C�X
		std::vector<PlaceModel*> adjacencies;

		//�A������
		std::vector<Adjacency> connectDirection;
	};
}

#endif