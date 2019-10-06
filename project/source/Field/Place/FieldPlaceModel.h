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
#define DEBUG_PLACEMODEL

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

		//�X�V�����A�`�揈��
		void Update();
		void Draw();

		//���W�擾
		FieldPosition GetPosition() const;

		//�אڃv���C�X�̒ǉ�
		void AddAdjacency(PlaceModel *adjacency, Adjacency type);
	
		//���[�g���n�߂��邩
		bool CanStartRoute();

		//���ɕς����邩
		bool ChangeableRoad();

		//�J��\�ȃ^�C�v��
		bool IsDevelopableType();

		//place�Ɨאڂ��Ă��邩
		Adjacency IsAdjacent(PlaceModel* place);

		//�A���ł���^�C�v��
		bool IsConnectableType();

		//�������[�g�ɑ����Ă��邩
		bool IsSameRoute(PlaceModel* place);

		//�A���Ώۂ̎擾
		PlaceModel* GetConnectTarget();		//TODO:�A���Ώۂ̕�����

		//�[�_�ƂȂ�Place�̎擾
		PlaceModel* GetEdgeOpponent();

		//���[�g���f���ւ̏����A���E
		void BelongRoute(std::shared_ptr<RouteModel> route);
		void BelongRoute(std::vector<std::shared_ptr<RouteModel>>& routes);
		void ExitRoute(std::shared_ptr<RouteModel> route);

		//�^�C�v����A�ύX����
		bool IsType(PlaceType type);
		void SetType(PlaceType type);

		//�������[�g�擾
		RouteModelPtr GetConnectingRoute();
		RouteContainer GetConnectingRoutes();

	private:
		//ID
		static unsigned incrementID;
		unsigned uniqueID;

		//�^�C�v�A���W
		PlaceType type;
		const FieldPosition Position;

		//�������Ă��郋�[�g�̎Q�ƃR���e�i
		std::vector<std::shared_ptr<RouteModel>> belongRouteList;

		//�אڃv���C�X
		std::vector<PlaceModel*> adjacencies;

		//�Q�[���ɕ\������A�N�^�[
		PlaceActor* actor;
	};
}

#endif