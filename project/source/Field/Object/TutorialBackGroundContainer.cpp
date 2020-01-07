//=============================================================================
//
// �`���[�g���A���p�n�ʃR���e�i�N���X [TutorialBackGroundContainer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "TutorialBackGroundContainer.h"

#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../FieldObject/Actor/RiverActor.h"
#include "../../FieldObject/Actor/NoneActor.h"
#include "../ActorLoader.h"

#include "../Place/PlaceConfig.h"

#include "../../../Framework/String/String.h"
#include "../../../Framework/Renderer3D/InstancingMeshContainer.h"
#include "../../../Framework/Core/ObjectPool.h"
#include "../../../Framework/Resource/ResourceManager.h"

#include <fstream>
#include <string>

namespace Field::Actor
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	TutorialBackGroundContainer::TutorialBackGroundContainer()
	{
		const unsigned ReserveSizeGround = 100;
		const unsigned ReserveSizeRiver = 10;

		groundContainer.reserve(ReserveSizeGround);
		riverContainer.reserve(ReserveSizeRiver);

		groundMesh = new InstancingMeshContainer(ReserveSizeGround);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	TutorialBackGroundContainer::~TutorialBackGroundContainer()
	{
		SAFE_DELETE(groundMesh);
	}

	/**************************************
	�X�V����
	***************************************/
	void TutorialBackGroundContainer::Update()
	{
		for (auto&& river : riverContainer)
		{
			river->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void TutorialBackGroundContainer::Draw()
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
	void TutorialBackGroundContainer::Load()
	{
		using Model::PlaceType;

		//CSV�t�@�C����ǂݍ���
		std::ifstream stream(Const::FieldDataFile[3]);

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

				FieldPosition position = Field::FieldPosition(x, z);

				if (type == PlaceType::River)
				{
					RiverActor *actor = ObjectPool::Instance()->Create<RiverActor>(position.ConvertToWorldPosition(), FieldLevel::City);
					riverContainer.push_back(actor);

					// ��̗���������Œ�
					actor->SetDirection((RiverActor::FlowDirection)0);
				}
				else
				{
					//�^�����炾�ƕs���R�Ȃ̂ō����ɏ������ʂ�����
					D3DXVECTOR3 offset = { 0.0f, Math::RandomRange(-2.0f, 0.0f), 0.0f };

					NoneActor *actor = ObjectPool::Instance()->Create<NoneActor>(position.ConvertToWorldPosition() + offset, FieldLevel::City);
					groundContainer.push_back(actor);
				}
				x++;
			}
			z++;
		}

		/*
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
				PlaceActor* actor = ObjectPool::Instance()->Create<NoneActor>(position, FieldLevel::City);
				groundContainer.push_back(actor);
			}
		}
#endif
*/
		//���b�V���R���e�i�쐬
		ResourceManager::Instance()->GetMesh(ActorLoader::GroundTag.c_str(), groundMesh);
		groundMesh->Init();
	}

	/**************************************
	�C����
	***************************************/
	bool TutorialBackGroundContainer::EnableAtlantis(const FieldPosition& position) const
	{
		//�C�͑��݂��Ȃ��̂Ŗ�������false
		return false;
	}

}