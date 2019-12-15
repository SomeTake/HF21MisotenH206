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
#include "../../../Framework/Tween/Tween.h"

namespace Field::Along
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	AlongController::AlongController(FieldLevel level) :
		currentLevel(level)
	{

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
		//Debug::Begin("Along");
		//if (Debug::Button("Growth"))
		//{
		//	for (auto&& pair : modelMap)
		//	{
		//		pair.second->CreateActor();
		//	}
		//}
		//Debug::End();

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
		//��U�R�����g�A�E�g
		//assert(modelMap.count(position) != 0);

		if (modelMap.count(position) == 0)
			return;

		modelMap[position]->CreateActor();
		addBuildBonus();
	}

	/**************************************
	��������_�����ꂽ���ɌĂ΂�鏈��
	***************************************/
	void AlongController::OnBuildRoad(const Transform & transform, RoadType type, bool onWater)
	{
		AlongPosition key = AlongPosition(transform.GetPosition());

		if (modelMap.count(key) == 0)
		{
			AlongModel *model = new AlongModel(currentLevel, onWater);
			modelMap.emplace(key, std::unique_ptr<AlongModel>(model));
		}

		modelMap[key]->SetType((AlongModel::Type)type);
		modelMap[key]->SetTransform(transform);
	}

	/**************************************
	���������h�����ۂ̃{�[�i�X����
	***************************************/
	void AlongController::SetBuildBonusFunc(const std::function<void()>& functor)
	{
		addBuildBonus = functor;
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
