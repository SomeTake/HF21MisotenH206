//=====================================
//
//�A�N�^�[���[�_�[����[ActorLoader.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ActorLoader.h"
#include "../../Library/json11/json11.hpp"
#include "../Field/FieldConfig.h"
#include "../../Framework/Resource/ResourceManager.h"

#include <string>
#include <fstream>

namespace Field::Actor
{
	/**************************************
	�^�E�����f���̃^�O
	***************************************/
	const std::string ActorLoader::CityTag[] = {
		"City-Town",
		"World-Town",
		"Space-Town"
	};

	/**************************************
	�J�[�u���̃^�O
	***************************************/
	const std::string ActorLoader::StraightTag[] = {
		"City-Straight",
		"World-Straight",
		"Space-Straight"
	};

	/**************************************
	�������̃^�O
	***************************************/
	const std::string ActorLoader::CurveTag[] = {
		"City-Curve",
		"World-Curve",
		"Space-Curve",
	};

	/**************************************
	T���H�̃^�O
	***************************************/
	const std::string ActorLoader::TJunctionTag[] = {
		"City-T",
		"World-T",
		"Space-T"
	};

	/**************************************
	�\���H�̃^�O
	***************************************/
	const std::string ActorLoader::CrossTag[] = {
		"City-Cross",
		"World-Cross",
		"Space-Cross"
	};

	/**************************************
	���̃^�O
	**************************************/
	const std::string ActorLoader::BridgeTag[] = {
		"City-Bridge",
		"World-Bridge",
		"Space-Bridge"
	};

	/**************************************
	�R�̃^�O
	***************************************/
	const std::string ActorLoader::MountainTag[] = {
		"City-Mountain",
		"World-Mountain",
		"Space-Mountain"
	};

	/**************************************
	����̃A�N�^�[�̃^�O
	***************************************/
	const std::string ActorLoader::WaterStraight = "World-StraightSea";
	const std::string ActorLoader::WaterCurve = "World-CurveSea";
	const std::string ActorLoader::WaterT = "World-TSea";
	const std::string ActorLoader::WaterCross = "World-CrossSea";

	/**************************************
	�Q���̃��\�[�X�^�O
	***************************************/
	const std::string ActorLoader::WhirlPoolTag = "World-WhirlPool";

	/**************************************
	�R���X�g���N�^
	***************************************/
	ActorLoader::ActorLoader()
	{

	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	ActorLoader::~ActorLoader()
	{
		modelFileName.clear();
	}

	/**************************************
	�ݒ�t�@�C���̓ǂݍ���	
	***************************************/
	void ActorLoader::LoadConfig()
	{
		//�ݒ�t�@�C�����J��
		std::string filePath = "data/PlaceActorConfig.txt";
		std::ifstream ifs;
		ifs.open(filePath, std::ios::in);

		//�����m�F
		assert(ifs.is_open());

		//JSON�f�[�^��ǂݍ���
		const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		ifs.close();

		std::string err;
		json11::Json data = json11::Json::parse(json, err);

		//�f�[�^���p�[�X
		for (int i = 0; i <= Field::FieldLevel::Space; i++)
		{
			modelFileName[CityTag[i]] = data[CityTag[i]].string_value();
			modelFileName[StraightTag[i]] = data[StraightTag[i]].string_value();
			modelFileName[CurveTag[i]] = data[CurveTag[i]].string_value();
			modelFileName[TJunctionTag[i]] = data[TJunctionTag[i]].string_value();
			modelFileName[CrossTag[i]] = data[CrossTag[i]].string_value();
			modelFileName[BridgeTag[i]] = data[BridgeTag[i]].string_value();
			modelFileName[MountainTag[i]] = data[MountainTag[i]].string_value();
			modelFileName[WaterStraight] = data[WaterStraight].string_value();
			modelFileName[WaterCurve] = data[WaterCurve].string_value();
			modelFileName[WaterT] = data[WaterT].string_value();
			modelFileName[WaterCross] = data[WaterCross].string_value();
			modelFileName[WhirlPoolTag] = data[WhirlPoolTag].string_value();
		}
	}

	/**************************************
	���\�[�X�ǂݍ���
	***************************************/
	void ActorLoader::LoadResource()
	{
		//���\�[�X��ǂݍ���
		for (auto&& pair : modelFileName)
		{
			if (pair.second == "")
				continue;

			ResourceManager::Instance()->LoadMesh(pair.first.c_str(), pair.second.c_str());
		}
	}
}