//=====================================
//
//SpaceBackGroundContainer.cpp
//�@�\:�F�����x���̔w�i�R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SpaceBackGroundContainer.h"

#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../FieldObject/Actor/RiverActor.h"

#include "../Place/PlaceConfig.h"

#include "../../../Framework/String/String.h"
#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"

#include "../../Effect/GameParticleManager.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	SpaceBackGroundContainer::SpaceBackGroundContainer()
	{
		//NoneActor�͕\�����Ȃ��̂�River�������U�[�u����
		const unsigned ReserveTearSize = 1000;

		//riverContainer.reserve(ReserveTearSize);

		//tearMesh = new InstancingMeshContainer(ReserveTearSize);
		//tearMesh->Load("data/MODEL/PlaceActor/SpaceTear.x");
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	SpaceBackGroundContainer::~SpaceBackGroundContainer()
	{
		//Utility::DeleteContainer(riverContainer);
	}

	/**************************************
	�X�V����
	***************************************/
	void SpaceBackGroundContainer::Update()
	{
	}

	/**************************************
	�`�揈��
	TODO:�������I�u�W�F�N�g���܂܂��̂Ő��䂷��
	***************************************/
	void SpaceBackGroundContainer::Draw()
	{
		//LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		//tearMesh->Lock();
		//for (auto&& tear : riverContainer)
		//{
		//	tearMesh->EmbedTranform(tear->GetTransform());
		//}
		//tearMesh->Unlock();

		//tearMesh->Draw();

		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}

	/**************************************
	�ǂݍ��ݏ���
	***************************************/
	void SpaceBackGroundContainer::Load()
	{
		using Model::PlaceType;

		//CSV�t�@�C����ǂݍ���
		std::ifstream stream(Const::FieldDataFile[FieldLevel::Space]);

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
				PlaceType type = Model::IntToPlaceType(std::stoi(str));

				D3DXVECTOR3 position = Field::FieldPosition(x, z).ConvertToWorldPosition();
				PlaceActor *actor = nullptr;

				if (type == PlaceType::River)
				{
					//actor = new RiverActor(position, FieldLevel::Space);
					//riverContainer.push_back(actor);

					//�p�[�e�B�N���̃G�~�b�^���Z�b�g
					D3DXVECTOR3 position = FieldPosition(x, z).ConvertToWorldPosition();
					GameParticleManager::Instance()->Generate(GameParticle::SpaceTear, position);
				}
				x++;
			}

			z++;
		}
	}
}