//=====================================
//
//OperatePlaceContainer.h
//�@�\:���삷��v���C�X���i�[����R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _OPERATEPLACECONTAINER_H_
#define _OPERATEPLACECONTAINER_H_

#include "../../../main.h"
#include <vector>

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class PlaceModel;

	/**************************************
	�N���X��`
	***************************************/
	class OperatePlaceContainer
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		OperatePlaceContainer();
		~OperatePlaceContainer();

		//�v���C�X�ǉ��J�n����
		bool Begin(PlaceModel* place);

		//�v���C�X�ǉ�����
		bool Add(PlaceModel* place);

		//�v���C�X�ǉ��I������
		bool End();

		//�R���e�i�N���A����
		void Clear();

		//�R���e�i�擾����
		std::vector<PlaceModel*> GetPlaces();

		//�f�o�b�O�\��
		void DrawDebug();

	private:
		std::vector<PlaceModel*> container;		//PlaceModel�R���e�i
	};
}
#endif