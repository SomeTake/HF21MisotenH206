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
#include "../../../Framework/Tool/ProfilerCPU.h"
#include "../../../Library/cppLinq/cpplinq.hpp"

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
		initialized(false),
		trafficJamRate(0.0f),
		trafficJamBias(0.0f)
	{
		placeVector.reserve(PlaceMax);

#ifdef DEBUG_PLACEMODEL
		//�f�o�b�O�\���p�̔|���S�����쐬����
		ResourceManager::Instance()->MakePolygon("None", "", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Road", "data/TEXTURE/PlaceTest/road.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Town", "data/TEXTURE/PlaceTest/town.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("River", "data/TEXTURE/PlaceTest/river.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Bridge", "data/TEXTURE/PlaceTest/Bridge.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Junction", "data/TEXTURE/PlaceTest/junction.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Mountain", "data/TEXTURE/PlaceTest/mountain.png", { 4.5f, 4.5f });
		ResourceManager::Instance()->MakePolygon("Operate", "data/TEXTURE/PlaceTest/operate.png", { 2.0f, 2.0f });
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

		//�f�o�b�O�\��
		Debug::Log("CntLinkedTown:%d", townContainer.size());
		Debug::Log("CntJunction:%d", junctionContainer.size());
		Debug::Log("TrafficJam: %f", trafficJamRate);
	}

#ifdef DEBUG_PLACEMODEL
	/**************************************
	�`�揈��
	***************************************/
	void PlaceContainer::DrawDebug()
	{
		if (!initialized)
			return;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		for (auto&& place : placeVector)
		{
			place->DrawDebug();
		}

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
#endif

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
	�O�v���C�X�擾����
	***************************************/
	std::vector<const PlaceModel*> Field::Model::PlaceContainer::GetAllPlaces() const
	{
		std::vector<const PlaceModel*> out;
		out.assign(placeVector.begin(), placeVector.end());
		return out;
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
	void Field::Model::PlaceContainer::OnConnectedTown(const PlaceModel * place)
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
	void Field::Model::PlaceContainer::OnCreateJunction(const PlaceModel * place)
	{
		unsigned placeID = place->ID();

		//�o�^�m�F
		if (junctionContainer.count(placeID) == 0)
		{
			junctionContainer.emplace(placeID, new JunctionModel(place));
		}
	}

	/**************************************
	�����N���x���̌v�Z
	***************************************/
	void Field::Model::PlaceContainer::CalcLinkLevel()
	{
		for (auto&& town : townContainer)
		{
			town.second->FindLinkedTown();
		}
	}

	/**************************************
	AI���W���x���v�Z
	***************************************/
	float Field::Model::PlaceContainer::CalcDevelopmentLevelAI(float bonus)
	{
		float developLevel = 0.0f;
		for (auto&& town : townContainer)
		{
			developLevel += town.second->DevelopmentLevel();
		}

		return developLevel;
	}

	/**************************************
	�X�S�̂̃����N���x������
	***************************************/
	void Field::Model::PlaceContainer::AddAllLinkLevel(int num)
	{
		for (auto&& town : townContainer)
		{
			town.second->AddLinkLevel(num);
		}
	}

	/**************************************
	�X��̃����N���x������
	***************************************/
	void Field::Model::PlaceContainer::AddLinkLevel(int num)
	{
		//�����_���ɑI�����ꂽ�X�Ƀ����N���x���𑫂�
		//����ׂɒ��o���邢�����@���v�������΂Ȃ�����
		int randomIndex = Math::RandomRange(0, (int)(townContainer.size()));
		int index = 0;
		for (auto&& town : townContainer)
		{
			if (index++ != randomIndex)
				continue;

			town.second->AddLinkLevel(num);
			return;
		}
	}

	/**************************************
	���G�x�����o�C�A�X�ݒ菈��
	***************************************/
	void Field::Model::PlaceContainer::SetTrafficjamBias(float bias)
	{
		trafficJamBias = bias;
	}

	/**************************************
	�j��Ώۃv���C�X�擾����
	***************************************/
	const PlaceModel * Field::Model::PlaceContainer::GetDestroyTarget()
	{
		using cpplinq::from;
		using cpplinq::where;
		using cpplinq::to_vector;

		auto townVector = from(placeVector)
			>> where([](auto& place)
		{
			return place->IsType(PlaceType::Town);
		})
			>> to_vector();

		int randomIndex = Math::RandomRange(0, (int)townVector.size() - 1);
		return townVector[randomIndex];
	}

	/**************************************
	�X������v���C�X�擾����
	***************************************/
	const PlaceModel * Field::Model::PlaceContainer::GetNonePlace()
	{
		using cpplinq::from;
		using cpplinq::where;
		using cpplinq::to_vector;

		//NOTE:���}��������B���Ƃł��ꂢ�Ɏ���
		auto noneVector = from(placeVector)
			>> where([](auto& place)
		{
			return place->IsType(PlaceType::None);
		})
			>> to_vector();

		int randomIndex = Math::RandomRange(0, (int)(noneVector.size() - 1));
		return noneVector[randomIndex];
	}

	/**************************************
	�X�j�󏈗�
	***************************************/
	void Field::Model::PlaceContainer::DestroyTown(const PlaceModel * target)
	{
		auto itrPlace = std::find(placeVector.begin(), placeVector.end(), target);

		if (itrPlace == placeVector.end())
			return;

		PlaceModel *place = *itrPlace;

		//���������Z�b�g
		RouteContainer belongRoute = place->GetConnectingRoutes();
		for (auto&& route : belongRoute)
		{
			place->ExitRoute(route);
		}

		//PlaceModel��None�^�C�v�ɕω�
		(*itrPlace)->SetType(PlaceType::None);

		//TownModel�폜
		SAFE_DELETE(townContainer[target->ID()]);
		townContainer.erase(target->ID());
	}

	/**************************************
	�X�쐬
	***************************************/
	void Field::Model::PlaceContainer::CreateTown(const PlaceModel * target)
	{
		auto itrPlace = std::find(placeVector.begin(), placeVector.end(), target);

		if (itrPlace == placeVector.end())
			return;

		PlaceModel* place = *itrPlace;
		place->SetType(PlaceType::Town);
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