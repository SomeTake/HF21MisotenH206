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

/**************************************
�O���錾
***************************************/
class BoardPolygon;

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class PlaceModel;
	class PinActor;

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
		bool BeginRoute(PlaceModel* place);
		bool BeginDevelop(PlaceModel* place);

		//�v���C�X�ǉ�����
		bool AddRoute(PlaceModel* place);
		bool AddDevelop(PlaceModel* place);

		//�v���C�X�ǉ��I������
		bool EndRoute();
		bool EndDevelop();

		//�R���e�i�N���A����
		void Clear();

		//�R���e�i�擾����
		std::vector<PlaceModel*> GetPlaces();

		//�f�o�b�O�\��
		void DrawDebug();

	private:
		std::vector<PlaceModel*> container;		//PlaceModel�R���e�i
	};

	/**************************************
	�s���A�N�^�[�N���X
	***************************************/
	class PinActor : GameObject
	{
	public:
		PinActor(const D3DXVECTOR3& position);
		~PinActor();

		void Draw();

	private:
		BoardPolygon *polygon;
	};
}
#endif