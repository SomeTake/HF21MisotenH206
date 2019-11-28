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
		enum Mode
		{
			BuildRoad,
			Develop
		};

		//�R���X�g���N�^�A�f�X�g���N�^
		OperatePlaceContainer();
		~OperatePlaceContainer();

		//�v���C�X�ǉ��J�n����
		bool BeginRoute(PlaceModel* place, bool isSea);
		bool BeginDevelop(PlaceModel* place, bool isSea);

		//�v���C�X�ǉ�����
		bool AddRoute(PlaceModel* place, bool isSea);
		bool AddDevelop(PlaceModel* place, bool isSea);

		//�v���C�X�ǉ��I������
		bool EndRoute();
		bool EndDevelop();

		//�R���e�i�N���A����
		void Clear();

		//�R���e�i�擾����
		std::vector<PlaceModel*> GetPlaces();

		//�X�V����
		void Update();

		//�f�o�b�O�\��
		void Draw();

	private:
		std::vector<PlaceModel*> container;		//PlaceModel�R���e�i
		std::vector<std::unique_ptr<PinActor>> actorContainer;	//PinActor�R���e�i

		void CreatePin(const PlaceModel* place, Mode mode, bool isSea);
	};

	/**************************************
	�s���A�N�^�[�N���X
	***************************************/
	class PinActor : GameObject
	{
	public:
		PinActor(const D3DXVECTOR3& position, OperatePlaceContainer::Mode mode, bool isSea);
		~PinActor();

		void Update();
		void Draw();

	private:
		BoardPolygon *polygon;
		bool isSea;
	};
}
#endif