//=====================================
//
//OperatePlaceContainer.cpp
//�@�\:����Ώۂ̃v���C�X���i�[����R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "OperatePlaceContainer.h"
#include "FieldPlaceModel.h"

#include <algorithm>

namespace Field::Model
{
	/**************************************
	using�錾
	***************************************/

	/**************************************
	�R���X�g���N�^
	***************************************/
	OperatePlaceContainer::OperatePlaceContainer()
	{
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	OperatePlaceContainer::~OperatePlaceContainer()
	{
		container.clear();
	}

	/**************************************
	�v���C�X�ǉ��J�n����
	***************************************/
	bool OperatePlaceContainer::Begin(PlaceModel * place)
	{
		//���[�g���n�߂���v���C�X�ł��邩�m�F
		if (!place->CanStartRoute())
			return false;

		//�R���e�i�ɒǉ�����return true
		container.push_back(place);

		return true;
	}

	/**************************************
	�v���C�X�ǉ�����
	***************************************/
	bool OperatePlaceContainer::Add(PlaceModel * place)
	{
		//�d���m�F
		auto itr = std::find(container.begin(), container.end(), place);
		if (itr != container.end())
			return false;

		//�אڔ���
		if (!place->IsAdjacent(*container.rbegin()))
			return false;

		//���ɏo���邩
		if (!place->ChangeableRoad())
			return false;

		//�ǉ�����return true
		container.push_back(place);

		return true;
	}

	/**************************************
	�ǉ��I������
	***************************************/
	bool OperatePlaceContainer::End()
	{
		//���[�g����������v���C�X�̐�
		const int validContainerSize = 2;

		//�v���C�X������Ă��Ȃ���΃R���e�i���N���A����return false
		if (container.size() < validContainerSize)
		{
			container.clear();
			return false;
		}

		//�Ō�ɒǉ������v���C�X�����[�g���n�߂���^�C�v�łȂ����return false
		PlaceModel* last = *container.rbegin();
		if (!last->CanStartRoute())
		{
			container.clear();
			return false;
		}

		return true;
	}

	/**************************************
	�R���e�i�N���A����
	***************************************/
	void OperatePlaceContainer::Clear()
	{
		container.clear();
		std::vector<PlaceModel*>().swap(container);
	}

	/**************************************
	�R���e�i�擾����
	***************************************/
	std::vector<PlaceModel*> OperatePlaceContainer::GetPlaces()
	{
		return container;
	}
}