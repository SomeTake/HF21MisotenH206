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
#include "../../../Framework/Tool/DebugWindow.h"

namespace Field::Along
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
		Debug::Begin("Along");
		if (Debug::Button("Growth"))
		{
			for (auto&& pair : modelMap)
			{
				pair.second->CreateActor();
			}
		}
		Debug::End();

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
		AlongPosition key = AlongPosition(transform.GetPosition());

		if (modelMap.count(key) == 0)
		{
			AlongModel *model = new AlongModel(transform);
			modelMap.emplace(key, std::unique_ptr<AlongModel>(model));
		}

		modelMap[key]->SetType((AlongModel::Type)type);
	}

	/**************************************
	AlongPosition�R���X�g���N�^
	***************************************/
	AlongPosition::AlongPosition(const D3DXVECTOR3 & position) :
		x(position.x), z(position.z)
	{
		
	}

	/**************************************
	AlongPosition < ���Z�q
	***************************************/
	bool AlongPosition::operator<(const AlongPosition & rhs) const
	{
		return std::tie(x, z) < std::tie(rhs.x, rhs.z);
	}
}
