//=====================================
//
//PlaceContainer.cpp
//�@�\:�v���C�X�R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldPlaceContainer.h"
#include "FieldPlaceModel.h"

namespace Field::Model
{
	/**************************************
	�O���[�o���ϐ�
	***************************************/

	/**************************************
	�R���X�g���N�^
	***************************************/
	PlaceContainer::PlaceContainer() :
		initialized(false)
	{
		placeVector.reserve(PlaceMax);


	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	PlaceContainer::~PlaceContainer()
	{
		Utility::DeleteContainer(placeVector);
	}

	/**************************************
	�X�V����
	***************************************/
	void PlaceContainer::Update()
	{
		if (!initialized)
			return;

		for (auto&& place : placeVector)
		{
			place->Update();
		}

	}

	/**************************************
	�`�揈��
	***************************************/
	void PlaceContainer::Draw()
	{
		if (!initialized)
			return;

		for (auto&& place : placeVector)
		{
			place->Draw();
		}
	}

	/**************************************
	�v���C�X�擾����
	***************************************/
	PlaceModel * PlaceContainer::GetPlace(int x, int z)
	{
		if (!initialized)
			return nullptr;

		if (x < 0 || x >= PlaceRowMax)
			return nullptr;

		if (z < 0 || z >= PlaceColumMax)
			return nullptr;

		return placeVector[PlaceColumMax * z + x];
	}

	/**************************************
	CSV�ǂݍ��ݏ���
	***************************************/
	void PlaceContainer::LoadCSV(const char * filePath)
	{
		if (initialized)
			return;



		initialized = true;
	}
}