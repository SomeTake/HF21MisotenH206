//=====================================
//
//�w�i�A�N�^�[�R���e�i����[BackGroundActorContainer.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BackGroundActorContainer.h"
#include "../../FieldObject/Actor/RiverActor.h"
#include "../../FieldObject/Actor/NoneActor.h"
#include "../Place/PlaceConfig.h"

#include "../../../Framework/String/String.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	BackGroundActorContainer::BackGroundActorContainer(FieldLevel level) :
		fieldLevel(level)
	{
		const unsigned ReserveSizeGround = 2500;
		const unsigned ReserveSizeRiver = 200;

		groundContainer.reserve(ReserveSizeGround);
		riverContainer.reserve(ReserveSizeRiver);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	BackGroundActorContainer::~BackGroundActorContainer()
	{
		Utility::DeleteContainer(groundContainer);
		Utility::DeleteContainer(riverContainer);
	}

	/**************************************
	�X�V����
	***************************************/
	void BackGroundActorContainer::Update()
	{
		for (auto&& ground : groundContainer)
		{
			ground->Update();
		}

		for (auto&& river : riverContainer)
		{
			river->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void BackGroundActorContainer::Draw()
	{
		for (auto&& ground : groundContainer)
		{
			ground->Draw();
		}

		for (auto&& river : riverContainer)
		{
			river->Draw();
		}
	}

	/**************************************
	�ǂݍ��ݏ���
	***************************************/
	void BackGroundActorContainer::Load()
	{
		using Model::PlaceType;

		const char* DataName[] =
		{
			//"data/FIELD/sample01.csv",
			"data/FIELD/City/City_Field.csv",
			"data/FIELD/World/World_Field.csv",
			"data/FIELD/Space/Space_Field.csv",
		};

		//CSV�t�@�C����ǂݍ���
		std::ifstream stream(DataName[fieldLevel]);

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
					actor = new RiverActor(position, fieldLevel);
					riverContainer.push_back(actor);
				}
				else
				{
					//�^�����炾�ƕs���R�Ȃ̂ō����ɏ������ʂ�����
					position.y += Math::RandomRange(-2.0f, 0.0f);

					actor = new NoneActor(position, fieldLevel);
					groundContainer.push_back(actor);
				}

				x++;
			}

			z++;
		}
	}
}