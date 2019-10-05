//=====================================
//
//PlaceContainer.cpp
//�@�\:�v���C�X�R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldPlaceContainer.h"
#include "FieldPlaceModel.h"
#include "../../../Framework/String/String.h"

#include <fstream>
#include <string>

#ifdef DEBUG_PLACEMODEL
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#endif

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

#ifdef DEBUG_PLACEMODEL
		ResourceManager::Instance()->MakePolygon("None", "", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Road", "data/TEXTURE/PlaceTest/road.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Town", "data/TEXTURE/PlaceTest/town.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("River", "data/TEXTURE/PlaceTest/river.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Bridge", "data/TEXTURE/PlaceTest/road.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Junction", "data/TEXTURE/PlaceTest/junction.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Mountain", "data/TEXTURE/PlaceTest/mountain.jpg", { 4.5f, 4.5f });
#endif
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
		if (x < 0 || x >= placeRowMax)
			return nullptr;

		if (z < 0 || z >= placeColumMax)
			return nullptr;

		return placeVector[placeColumMax * z + x];
	}

	/**************************************
	CSV�ǂݍ��ݏ���
	***************************************/
	void PlaceContainer::LoadCSV(const char * filePath)
	{
		//�������ς݂ł���΃��^�[��
		if (initialized)
			return;
		
		//CSV�t�@�C����ǂݍ���
		std::ifstream stream(filePath);

		std::string line;			//CSV��1�s���ǂރo�b�t�@
		const char Delim = ',';		//��؂蕶��
		int x = 0;					//Place��X�ʒu
		int z = 0;					//Place��Z�ʒu

		//CSV�̏I���܂œǂݍ��ݑ�����
		while (std::getline(stream, line))
		{
			//1�s���ǂݍ��񂾃f�[�^����؂蕶���ŕ�������
			std::vector<std::string> subStr;
			String::Split(subStr, line, Delim);
		
			x = 0;

			//���������f�[�^����PlaceModel���쐬
			for (auto&& str : subStr)
			{
				PlaceType type = IntToPlaceType(std::stoi(str));
				PlaceModel *place = new PlaceModel(type, x, z);
				placeVector.push_back(place);

				x++;
			}

			z++;
		}

		//�R���e�i�̍s���Ɨ񐔂�ۑ�
		placeRowMax = x;
		placeColumMax = z;

		//�אڏ��쐬
		MakeAdjacency();

		//����������
		initialized = true;
	}

	/**************************************
	�אڏ��쐬
	***************************************/
	void PlaceContainer::MakeAdjacency()
	{
		for (int z = 0; z < placeColumMax; z++)
		{
			for (int x = 0; x < placeColumMax; x++)
			{
				//�Ώۂ̃v���C�X�̗אڃv���C�X�����ꂼ��擾
				PlaceModel* back = GetPlace(x, z - 1);
				PlaceModel* left = GetPlace(x - 1, z);
				PlaceModel* forward = GetPlace(x, z + 1);
				PlaceModel* right = GetPlace(x + 1, z);

				//�אڃv���C�X�ݒ�
				PlaceModel *place = GetPlace(x, z);
				place->AddAdjacency(back, Adjacency::Back);
				place->AddAdjacency(left, Adjacency::Left);
				place->AddAdjacency(forward, Adjacency::Forward);
				place->AddAdjacency(right, Adjacency::Right);
			}
		}
	}
}