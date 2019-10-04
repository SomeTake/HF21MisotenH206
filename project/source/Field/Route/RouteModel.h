//=====================================
//
//RouteModel.h
//�@�\:�q����������\�����f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ROUTEMODEL_H_
#define _ROUTEMODEL_H_

#include "../../../main.h"

#include <vector>

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class PlaceModel;
	class RouteModel;

	typedef std::shared_ptr<RouteModel> RouteModelPtr;

	/**************************************
	�אڃ��[�g���
	***************************************/
	typedef struct _AdjacentRoute
	{
		PlaceModel *start, *end;
		std::weak_ptr<RouteModel> route;

		//�R���X�g���N�^
		_AdjacentRoute(PlaceModel* start, PlaceModel* end, std::shared_ptr<RouteModel>& route) :
			start(start), end(end), route(route) {};

	}AdjacentRoute;

	/**************************************
	�N���X��`
	***************************************/
	class RouteModel : public std::enable_shared_from_this<RouteModel>
	{
		friend class RouteProcessor;
	public:
		//�R���X�g���N�^
		RouteModel();

		//Create�֐��ł��̃N���X��shared_ptr���쐬������
		static RouteModelPtr Create();
		static RouteModelPtr Create(const std::vector<PlaceModel*>& placeVector);

		//�f�X�g���N�^
		~RouteModel();		//�����𗣒E

		//�X�V����
		void Update();

		//���[�g�ƂȂ铹��ǉ�
		void AddRoad(PlaceModel* place);

		//�אڃ��[�g�ǉ�
		void AddAdjacency(PlaceModel* junction, PlaceModel* connectTarget, std::shared_ptr<RouteModel> opponent);
		void AddAdjacency(const std::vector<AdjacentRoute>& adjacenctRoute);

		//�[�_�ݒ�
		void SetEdge();
		void SetEdge(PlaceModel* edge);

		//�[�_�擾
		PlaceModel* GetOtherEdge(PlaceModel* edge);

		//�q�����Ă���X���擾
		PlaceModel* GetConnectedTown(PlaceModel* self);

		//�g�p����
		void SetUnused(bool use);
		bool IsUnused();

	private:
		PlaceModel *edgeStart, *edgeEnd;			//�[�_��Place
		std::vector<PlaceModel*> route;				//���ƂȂ�Place
		std::vector<AdjacentRoute> adjacentRoute;	//�אڃ��[�g�̃R���e�i

		static unsigned incrementID;				//�C���N�������gID
		unsigned uniqueID;							//�C���X�^���X�ŗL��ID

		bool isUnused;								//�g�p����

		void _SetEdge(PlaceModel* place);			//�[�_�ݒ��������
	};
}
#endif