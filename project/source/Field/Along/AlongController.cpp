//=====================================
//
//AlongController.cpp
//�@�\:�������̏��R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "AlongController.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "AlongModel.h"

namespace Field
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	AlongController::AlongController()
	{
		ResourceManager::Instance()->LoadMesh("AlongActor", "data/MODEL/AlongActor/AlongActor.x");
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	AlongController::~AlongController()
	{
		modelMap.clear();
	}

	/**************************************
	�X�V����
	***************************************/
	void AlongController::Update()
	{
		for (auto&& pair : modelMap)
		{
			pair.second->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void AlongController::Draw()
	{
		for (auto&& pair : modelMap)
		{
			pair.second->Draw();
		}
	}

	/**************************************
	Passenger��Place�ɓ��B�����ۂ̏���
	***************************************/
	void AlongController::OnReachPassenger(const D3DXVECTOR3 & position)
	{
		assert(modelMap.count(position) != 0);

		modelMap[position]->CreateActor();
	}

	/**************************************
	��������_�����ꂽ���ɌĂ΂�鏈��
	***************************************/
	void AlongController::OnBuildRoad(const Transform & transform, RoadType type)
	{
		D3DXVECTOR3 position = transform.GetPosition();

		if (modelMap.count(position) == 0)
		{
			Along::AlongModel *model = new Along::AlongModel(transform);
			modelMap.emplace(position, std::unique_ptr<Along::AlongModel>(model));
		}

		modelMap[position]->SetType((Along::AlongModel::Type)type);
	}
}
