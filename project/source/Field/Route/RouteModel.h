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
	class RouteModel
	{
	public:
		//�[�_�̎�ނ�\���񋓎q
		enum Edge
		{
			Start,		//�n�_
			End,		//�I�_
			Max
		};

		//�R���X�g���N�^�A�f�X�g���N�^
		RouteModel();
		RouteModel(const std::vector<PlaceModel*>& routes);
		~RouteModel();		//�����𗣒E

		//�X�V����
		void Update();

		//���[�g�ƂȂ铹��ǉ�
		void AddRoad(PlaceModel* place);

		//�אڃ��[�g�ǉ�
		void AddAdjacency(PlaceModel* junction, PlaceModel* connectTarget, std::shared_ptr<RouteModel> opponent);
		void AddAdjacency(const std::vector<AdjacentRoute>& adjacenctRoute);

		//�אڃ��[�g�擾
		std::vector<AdjacentRoute> GetAdjacencies();

		//�[�_�ݒ�
		void SetEdge();
		void SetEdge(PlaceModel* edge);

		//�[�_�擾
		PlaceModel* GetEdge(Edge type);
		PlaceModel* GetOtherEdge(PlaceModel* edge);

		//�q�����Ă���X���擾
		PlaceModel* GetConnectedTown(PlaceModel* self);

		//���[�g�ƂȂ�v���C�X�̎擾
		std::vector<PlaceModel*> GetRoute();

	private:
		PlaceModel *edgeStart, *edgeEnd;			//�[�_��Place
		std::vector<PlaceModel*> route;				//���ƂȂ�Place
		std::vector<AdjacentRoute> adjacentRoute;	//�אڃ��[�g�̃R���e�i

		static unsigned incrementID;				//�C���N�������gID
		unsigned uniqueID;							//�C���X�^���X�ŗL��ID

		void _SetEdge(PlaceModel* place);			//�[�_�ݒ��������
	};
}
#endif