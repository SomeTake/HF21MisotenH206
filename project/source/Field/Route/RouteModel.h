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
#include "../../../Framework/Pattern/Delegate.h"
#include "../Place/PlaceConfig.h"

#include <vector>
#include <functional>

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class PlaceModel;
	class RouteModel;
	class TownModel;

	using RouteModelPtr = std::shared_ptr<RouteModel>;
	using CallbackConnect = std::function<void(const PlaceModel*, const PlaceModel*)>;

	
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
		RouteModel(CallbackConnect& onConnectTown);

		bool operator ==(const RouteModel& rhs) const;

		//Create�֐��ł��̃N���X��shared_ptr���쐬������
		static RouteModelPtr Create(CallbackConnect& onConnectTown);
		static RouteModelPtr Create(CallbackConnect& onConnectTown, const std::vector<PlaceModel*>& placeVector);

		//�f�X�g���N�^
		~RouteModel();		//�����𗣒E

		//�X�V����
		void Update();

		//���[�g�ƂȂ铹��ǉ�
		void AddRoad(PlaceModel* place);

		//�v���C�X�̏�������
		void BreakAway();

		//�אڃ��[�g�ǉ�
		void AddAdjacency(PlaceModel* junction, PlaceModel* connectTarget, std::shared_ptr<RouteModel> opponent);
	
		//�[�_�ݒ�
		void SetEdge();
		void SetEdge(PlaceModel* edge);

		//�[�_�擾
		PlaceModel* GetOtherEdge(const PlaceModel* edge);

		//�q�����Ă���X���擾
		PlaceModel* GetConnectedTown(const PlaceModel* self);

		//���[�g�Ɍq�����Ă���X�̒T��
		int FindLinkedTown(TownModel* root, std::vector<unsigned>& searchedRoute);

		//�g�p����
		void SetUnused(bool use);
		bool IsUnused();

		//�S�v���C�X�擾
		const std::vector<const PlaceModel*> GetAllPlaces(const PlaceModel* start = nullptr) const;

		//�n�_�A�I�_�擾����
		PlaceModel* GetFirst() const;
		PlaceModel* GetLast() const;

		// ��������̐����擾
		int GetRoadNum(void) { return this->route.size(); };

	private:
		PlaceModel *edgeStart, *edgeEnd;			//�[�_��Place
		std::vector<PlaceModel*> route;				//���ƂȂ�Place
		std::vector<AdjacentRoute> adjacentRoute;	//�אڃ��[�g�̃R���e�i

		static unsigned incrementID;				//�C���N�������gID
		unsigned uniqueID;							//�C���X�^���X�ŗL��ID

		bool isUnused;								//�g�p����

		CallbackConnect onConnectedTown;			//�X�Ɠ����q�������Ƃ��̃R�[���o�b�N

		void _SetEdge(PlaceModel* place);			//�[�_�ݒ��������
	};
}
#endif