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
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Renderer3D/SkyBox.h"

#include "../../Effect/SpaceParticleManager.h"

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
		const unsigned ReserveTearSize = 2500;
		riverContainer.reserve(ReserveTearSize);

		tearMesh = new InstancingMeshContainer(ReserveTearSize);

		skybox = new SkyBox({ 20000.0f, 20000.0f, 20000.0f });
		for (int i = 0; i < SkyBox::Surface::Max; i++)
		{
			skybox->LoadTexture("data/MODEL/PlaceActor/spacePlasma.jpg", SkyBox::Surface(i));
		}
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	SpaceBackGroundContainer::~SpaceBackGroundContainer()
	{
		Utility::DeleteContainer(riverContainer);
		SAFE_DELETE(tearMesh);
		SAFE_DELETE(skybox);
	}

	/**************************************
	�X�V����
	***************************************/
	void SpaceBackGroundContainer::Update()
	{
	}

	/**************************************
	�`�揈��
	***************************************/
	void SpaceBackGroundContainer::Draw()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//�X�e���V���Ń}�X�N���쐬
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00);
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		pDevice->Clear(0, 0, D3DCLEAR_STENCIL, 0, 0.0f, 0);

		tearMesh->Lock();
		for (auto&& tear : riverContainer)
		{
			bool res = tearMesh->EmbedTranform(tear->GetTransform());
			if (!res)
				break;
		}
		tearMesh->Unlock();

		tearMesh->Draw();

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_STENCILREF, 1);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESS);
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
			D3DCOLORWRITEENABLE_RED |
			D3DCOLORWRITEENABLE_GREEN |
			D3DCOLORWRITEENABLE_BLUE |
			D3DCOLORWRITEENABLE_ALPHA);


		//�􂯖ڂ�`��
		skybox->Draw();

		pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
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
					actor = new RiverActor();
					actor->Init(position, FieldLevel::Space);
					riverContainer.push_back(actor);

					//�p�[�e�B�N���̃G�~�b�^���Z�b�g
					//D3DXVECTOR3 position = FieldPosition(x, z).ConvertToWorldPosition();
					//position.y -= 2.5f;
					//SpaceParticleManager::Instance()->Generate(SpaceParticle::SpaceTear, position);
				}
				x++;
			}

			z++;
		}

		ResourceManager::Instance()->GetMesh("River-Space", tearMesh);
		tearMesh->Init();
	}

	/**************************************
	�C����
	***************************************/
	bool SpaceBackGroundContainer::EnableAtlantis(const FieldPosition& position) const
	{
		//�C�͑��݂��Ȃ��̂Ŗ�������false
		return false;
	}
}