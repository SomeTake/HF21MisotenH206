//=====================================
//
//�w�i�A�N�^�[�R���e�i����[CityBackGroundContainer.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "CityBackGroundContainer.h"

#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../FieldObject/Actor/RiverActor.h"
#include "../../FieldObject/Actor/NoneActor.h"

#include "../Place/PlaceConfig.h"

#include "../../../Framework/String/String.h"
#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	CityBackGroundContainer::CityBackGroundContainer()
	{
		const unsigned ReserveSizeGround = 10000;
		const unsigned ReserveSizeRiver = 200;

		groundContainer.reserve(ReserveSizeGround);
		riverContainer.reserve(ReserveSizeRiver);

		groundMesh = new InstancingMeshContainer(ReserveSizeGround);
		groundMesh->Load("data/MODEL/PlaceActor/ground.x");
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	CityBackGroundContainer::~CityBackGroundContainer()
	{
		Utility::DeleteContainer(groundContainer);
		Utility::DeleteContainer(riverContainer);

		SAFE_DELETE(groundMesh);
	}

	/**************************************
	�X�V����
	***************************************/
	void CityBackGroundContainer::Update()
	{
		for (auto&& river : riverContainer)
		{
			river->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void CityBackGroundContainer::Draw()
	{
		//�n�ʂ̓C���X�^���V���O�ŕ`�悷��
		groundMesh->Lock();
		for (auto&& ground : groundContainer)
		{
			bool result = groundMesh->EmbedTranform(ground->GetTransform());
			if (!result)
				break;
		}
		groundMesh->Unlock();

		groundMesh->Draw();

		for (auto&& river : riverContainer)
		{
			river->Draw();
		}
	}

	/**************************************
	�ǂݍ��ݏ���
	***************************************/
	void CityBackGroundContainer::Load()
	{
		using Model::PlaceType;

		//CSV�t�@�C����ǂݍ���
		std::ifstream stream(Const::FieldDataFile[0]);

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
					actor = new RiverActor(position, FieldLevel::City);
					riverContainer.push_back(actor);
				}
				else
				{
					//�^�����炾�ƕs���R�Ȃ̂ō����ɏ������ʂ�����
					position.y += Math::RandomRange(-2.0f, 0.0f);

					actor = new NoneActor(position, FieldLevel::City);
					groundContainer.push_back(actor);
				}

				x++;
			}

			z++;
		}

#ifndef _DEBUG
		//�t�B�[���h�̊O���̔w�i�����
		//NOTE:�Ƃ肠�����Ȃ̂őS���n�ʂɂ��Ă��܂�
		const int MaxOuter = 25;
		for (int outerX = -MaxOuter; outerX < x + MaxOuter; outerX++)
		{
			for (int outerZ = -MaxOuter; outerZ < z + MaxOuter; outerZ++)
			{
				if (outerX >= 0 && outerX < x && outerZ >= 0 && outerZ < z)
					continue;

				D3DXVECTOR3 position = FieldPosition(outerX, outerZ).ConvertToWorldPosition();
				position.y += Math::RandomRange(-2.0f, 0.0f);
				PlaceActor * actor = new NoneActor(position, FieldLevel::City);
				groundContainer.push_back(actor);
			}
		}
#endif
	}
}