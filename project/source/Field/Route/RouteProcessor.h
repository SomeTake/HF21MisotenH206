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
#include "../../../Framework/Pattern/Delegate.h"

#include <vector>

namespace Field::Model
{
	/**************************************
	�N���X��`
	***************************************/
	class RouteProcessor
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		RouteProcessor(DelegatePtr<const PlaceModel*> onChangePlaceType);
		RouteProcessor() {}

		//�V������������[�g�ɑ΂��ėאڂ��Ă��郋�[�g�ƘA�������ĉ��H����
		void Process(RouteModelPtr& model, RouteContainer& routeContainer);

		//�V������������[�g��[�_�ő��ƘA��������
		void ConnectWithEdge(RouteModelPtr& model, RouteContainer& routeContainer);

		//���[�g�����Ă����v���C�X�ŕ�������
		RouteContainer Divide(RouteModelPtr& model, PlaceModel* junction, RouteContainer& routeContainer);

	private:
		//�v���C�X�^�C�v��ω��������ۂ̃f���Q�[�g
		DelegatePtr<const PlaceModel*> onChangePlaceType;

		void _ConnectWithEdge(RouteModelPtr& model, PlaceModel *place, RouteContainer& routeContainer);
	};
}

#endif