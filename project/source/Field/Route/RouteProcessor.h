//=====================================
//
//RouteProcessor.h
//�@�\:���[�g���f���𑀍삷��N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ROUTEPROCESSOE_H_
#define _ROUTEPROCESSOE_H_

#include "../../../main.h"
#include "../Place/PlaceConfig.h"

#include <vector>

namespace Field::Model
{
	/**************************************
	�N���X��`
	***************************************/
	class RouteProcessor
	{
	public:
		//�V������������[�g�ɑ΂��ėאڂ��Ă��郋�[�g�ƘA�������ĉ��H����
		static void Process(RouteModelPtr& model, RouteContainer& routeContainer);

		//�V������������[�g��[�_�ő��ƘA��������
		static void ConnectWithEdge(RouteModelPtr& model, RouteContainer& routeContainer);

		//���[�g�����Ă����v���C�X�ŕ�������
		static RouteContainer Divide(RouteModelPtr& model, PlaceModel* junction, RouteContainer& routeContainer);

		//���[�g�Ɍq�����Ă���X�̒T��
		static int FindLinkedTown(const PlaceModel* root, RouteModelPtr target, RouteContainer& searchedRoute, std::vector<PlaceModel*> searchedTown);

	private:
		RouteProcessor() {}

		static void _ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer);
	};
}

#endif