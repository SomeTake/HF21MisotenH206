//=====================================
//
//WorldBackGroundContainer.cpp
//�@�\:World���x���̔w�i�R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "WorldBackGroundContainer.h"
#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../FieldObject/Actor/RiverActor.h"
#include "../../FieldObject/Actor/NoneActor.h"
#include "../ActorLoader.h"

#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"
#include "../../../Framework/String/String.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Resource/ResourceManager.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	WorldBackGroundContainer::WorldBackGroundContainer()
	{
		//riverContainer���C�Ƃ��Ĉ���
		const unsigned ReserveSizeSea = 10000;
		const unsigned ReserveSizeGround = 2000;

		riverContainer.reserve(ReserveSizeSea);
		groundContainer.reserve(ReserveSizeGround);
		seaMap.reserve(ReserveSizeSea);

		groundMesh = new InstancingMeshContainer(ReserveSizeGround);
		seaMesh = new InstancingMeshContainer(ReserveSizeSea);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	WorldBackGroundContainer::~WorldBackGroundContainer()
	{
		SAFE_DELETE(groundMesh);
		SAFE_DELETE(seaMesh);
	}

	/**************************************
	�X�V����
	***************************************/
	void WorldBackGroundContainer::Update()
	{
		for (auto&& sea : riverContainer)
		{
			sea->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void WorldBackGroundContainer::Draw()
	{
		//�n�ʂ̕`��
		groundMesh->Lock();
		for (auto&& ground : groundContainer)
		{
			bool res = groundMesh->EmbedTranform(ground->GetTransform());
			if (!res)
				break;
		}
		groundMesh->Unlock();

		groundMesh->Draw();

		//�C�̕`��
		seaMesh->Lock();
		for (auto&& sea : riverContainer)
		{
			bool res = seaMesh->EmbedTranform(sea->GetTransform());
			if (!res)
				break;
		}
		seaMesh->Unlock();

		seaMesh->Draw();
	}

	/**************************************
	�ǂݍ��ݏ���
	***************************************/
	void WorldBackGroundContainer::Load(int csvNo)
	{
		using Model::PlaceType;

		//CSV�t�@�C����ǂݍ���
		std::ifstream layerData(Const::FieldLayerFile[csvNo]);

		std::string layerLine;
		const char Delim = ',';		//��؂蕶��
		int x = 0;					//Place��X�ʒu
		int z = 0;					//Place��Z�ʒu

		//CSV�̏I���܂œǂݍ��ݑ�����
		while (std::getline(layerData, layerLine))
		{
			//1�s���ǂݍ��񂾃f�[�^����؂蕶���ŕ�������
			std::vector<std::string> subStrLayer;
			String::Split(subStrLayer, layerLine, Delim);

			x = 0;

			//���������f�[�^����PlaceModel���쐬
			for(auto&& layer : subStrLayer)
			{
				int type = std::stoi(layer);

				D3DXVECTOR3 position = Field::FieldPosition(x, z).ConvertToWorldPosition();
				PlaceActor *actor = nullptr;

				if (type == FieldLayer::Sea)
				{
					actor = ObjectPool::Instance()->Create<RiverActor>(position, FieldLevel::City);		//City�Ɠ����Ȃ̂łƂ肠����
					riverContainer.push_back(actor);

					//seaMap�ɒǉ�
					seaMap.push_back(FieldPosition(x, z));
				}
				else
				{
					//�^�����炾�ƕs���R�Ȃ̂ō����ɏ������ʂ�����
					position.y += Math::RandomRange(-2.0f, 0.0f);
					actor = ObjectPool::Instance()->Create<NoneActor>(position, Field::FieldLevel::City);
					groundContainer.push_back(actor);
				}

				x++;
			}

			z++;
		}

#ifndef _DEBUG
		//�t�B�[���h�̊O���̔w�i�����
		//NOTE:�Ƃ肠�����Ȃ̂őS���C�ɂ��Ă��܂�
		const int MaxOuter = 25;
		for (int outerX = -MaxOuter; outerX < x + MaxOuter; outerX++)
		{
			for (int outerZ = -MaxOuter; outerZ < z + MaxOuter; outerZ++)
			{
				if (outerX >= 0 && outerX < x && outerZ >= 0 && outerZ < z)
					continue;

				D3DXVECTOR3 position = FieldPosition(outerX, outerZ).ConvertToWorldPosition();
				PlaceActor *actor = ObjectPool::Instance()->Create<RiverActor>(position, FieldLevel::City);
				riverContainer.push_back(actor);
			}
		}
#endif

		//���b�V���R���e�i�쐬
		ResourceManager::Instance()->GetMesh(ActorLoader::WorldGroundTag.c_str(), groundMesh);
		groundMesh->Init();

		ResourceManager::Instance()->GetMesh(ActorLoader::SeaTag.c_str(), seaMesh);
		seaMesh->Init();
	}

	/**************************************
	�C����
	***************************************/
	bool WorldBackGroundContainer::IsSeaPlace(const FieldPosition & position) const
	{
		return Utility::IsContain(seaMap, position);
	}

	/**************************************
	�A�g�����e�B�X����	
	***************************************/
	bool WorldBackGroundContainer::EnableAtlantis(const FieldPosition & position) const
	{
		//����8�}�X���܂߂��͈͂��m�F
		for (int x = -1; x <= 1; x++)
		{
			for (int z = -1; z <= 1; z++)
			{
				FieldPosition SearchPosition = FieldPosition(x, z) + position;

				if (!Utility::IsContain(seaMap, SearchPosition))
					return false;
			}
		}

		return true;
	}

	/**************************************
	�A�g�����e�B�X�Z�b�g����
	***************************************/
	void WorldBackGroundContainer::CreateAtlantis(const FieldPosition & position)
	{
		const D3DXVECTOR3 InitOffset = Vector3::Down * 10.0f;

		for (int x = -1; x <= 1; x++)
		{
			for (int z = -1; z <= 1; z++)
			{
				FieldPosition fieldPos = position + FieldPosition(x, z);
				D3DXVECTOR3 worldPosition = fieldPos.ConvertToWorldPosition();
				PlaceActor *actor = ObjectPool::Instance()->Create<NoneActor>(worldPosition + InitOffset, FieldLevel::City);
				groundContainer.push_back(actor);

				//�C���点��オ���Ă���A�j���[�V����
				Tween::Move(*actor, worldPosition + InitOffset, worldPosition, 60, EaseType::InOutCirc);

				//�n�`���̍X�V
				auto itr = std::remove(seaMap.begin(), seaMap.end(), fieldPos);
				seaMap.erase(itr, seaMap.end());
			}
		}
	}
}