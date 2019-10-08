//=====================================
//
//PlaceContainer.cpp
//�@�\:�v���C�X�R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldPlaceContainer.h"
#include "FieldPlaceModel.h"
#include "FieldTownModel.h"
#include "FieldJunctionModel.h"
#include "../../../Framework/String/String.h"
#include "../../../Framework/Tool/DebugWindow.h"

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
		placeRowMax(0),
		placeColumMax(0),
		initialized(false)
	{
		placeVector.reserve(PlaceMax);

#ifdef DEBUG_PLACEMODEL
		//�f�o�b�O�\���p�̔|���S�����쐬����
		ResourceManager::Instance()->MakePolygon("None", "", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Road", "data/TEXTURE/PlaceTest/road.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Town", "data/TEXTURE/PlaceTest/town.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("River", "data/TEXTURE/PlaceTest/river.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Bridge", "data/TEXTURE/PlaceTest/Bridge.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Junction", "data/TEXTURE/PlaceTest/junction.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Mountain", "data/TEXTURE/PlaceTest/mountain.jpg", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Operate", "data/TEXTURE/PlaceTest/operate.jpg", { 2.0f, 2.0f });
#endif
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	PlaceContainer::~PlaceContainer()
	{
		Utility::DeleteContainer(placeVector);

		Utility::DeleteMap(townContainer);
		Utility::DeleteMap(junctionContainer);
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

		//�f�o�b�O�\��
		Debug::Log("CntLinkedTown:%d", townContainer.size());
		Debug::Log("CntJunction:%d", junctionContainer.size());
		Debug::Log("TrafficJam: %f", CaclTrafficJamRate());

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
	�v���C�X�擾����
	***************************************/
	PlaceModel* PlaceContainer::GetPlace(const FieldPosition& position)
	{
		if (position.x < 0 || position.x >= placeRowMax)
			return nullptr;

		if (position.z < 0 || position.z >= placeColumMax)
			return nullptr;

		return placeVector[placeColumMax * position.z + position.x];
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
	�s�A��̍ő吔�擾
	***************************************/
	FieldPosition Field::Model::PlaceContainer::GetPlaceBorder() const
	{
		return FieldPosition(placeRowMax, placeColumMax);
	}

	/**************************************
	�X�����ƌq�������Ƃ��̏���
	***************************************/
	void Field::Model::PlaceContainer::OnConnectedTown(PlaceModel * place)
	{
		unsigned placeID = place->ID();

		//�o�^�m�F
		if (townContainer.count(placeID) == 0)
		{
			townContainer.emplace(placeID, new TownModel(place));
		}

		townContainer[placeID]->AddGate();
	}

	/**************************************
	�����_�����ꂽ�Ƃ��̏���
	***************************************/
	void Field::Model::PlaceContainer::OnCreateJunction(PlaceModel * place)
	{
		unsigned placeID = place->ID();

		//�o�^�m�F
		if (junctionContainer.count(placeID) == 0)
		{
			junctionContainer.emplace(placeID, new JunctionModel(place));
		}
	}

	/**************************************
	���G�x�v�Z
	***************************************/
	float Field::Model::PlaceContainer::CaclTrafficJamRate()
	{
		//�o��������X���Ȃ���Όv�Z���������Ȃ��̂ő������^�[��
		if (townContainer.empty())
			return 1.0f;

		int sumGate = 0;
		for (auto&& town : townContainer)
		{
			sumGate += town.second->GateNum();
		}

		//�����_�������ꍇ�̌v�Z��
		if (junctionContainer.empty())
		{
			return ((float)townContainer.size() / sumGate);
		}
		//�����_������ꍇ�̌v�Z��
		else
		{
			float sumTrafficJam = 0.0f;
			int validJunctionNum = 0;

			for (auto&& junction : junctionContainer)
			{
				float trafficJam = junction.second->TrafficJam(townContainer);

				if (trafficJam == 0.0f)
					continue;

				sumTrafficJam += trafficJam;
				validJunctionNum++;
			}

			return Math::Min(sumTrafficJam * 0.01f * 1.5f / (validJunctionNum * sumGate), 1.0f);
		}
	}

	/**************************************
	AI���W���x���v�Z
	***************************************/
	float Field::Model::PlaceContainer::CalcDevelopmentLevelAI()
	{
		float trafficJamRate = CaclTrafficJamRate();

		float developLevel = 0.0f;
		for (auto&& town : townContainer)
		{
			developLevel += town.second->OnGrowth(1.0f - trafficJamRate);
		}

		return developLevel;
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