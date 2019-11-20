//=====================================
//
// �p�b�Z���W���[�R���g���[��[PassengerController.cpp]
// �@�\�F�p�b�Z���W���[�Ǘ��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PassengerController.h"
#include <algorithm>
#include <fstream>
#include <string>
#include "../../Framework/String/String.h"
#include "../../Framework/Resource/ResourceManager.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const int PassengerController::PassengerReserve = 1000;

//=====================================
// �R���X�g���N�^
//=====================================
PassengerController::PassengerController(Field::FieldLevel level) :
	callback(nullptr), currentLevel(level)
{
	modelVector.reserve(PassengerReserve);
}

//=====================================
// �f�X�g���N�^
//=====================================
PassengerController::~PassengerController()
{
	for (auto& vec : modelVector)
	{
		SAFE_DELETE(vec);
	}
	modelVector.clear();
}

//=====================================
// �X�V
//=====================================
void PassengerController::Update()
{
	for (auto& actor : modelVector)
	{
		actor->Update();
	}

	if (currentLevel == Field::World)
	{
		// ���b�V���؂�ւ��̊m�F
		CheckPassengerMesh();
	}
}

//=====================================
// �`��
//=====================================
void PassengerController::Draw()
{
	for (auto& actor : modelVector)
	{
		actor->Draw();
	}
}

//=====================================
// �p�b�Z���W���[�̃Z�b�g
//=====================================
void PassengerController::SetPassenger(std::deque<D3DXVECTOR3>& root)
{
	bool check = false;
	int sub = 0;
	// vector�̓����ɖ��g�p�̂��̂����邩�m�F
	for (auto& vec : modelVector)
	{
		if (!vec->IsActive())
		{
			check = true;
			break;
		}
		sub++;
	}

	if (check)
	{
		modelVector[sub]->SetActor(root, currentLevel);
	}
	else
	{
		PassengerModel *model = new PassengerModel(root, currentLevel, &callback);
		modelVector.push_back(model);
	}
}

//=====================================
// �R�[���o�b�N�ݒ菈��
//=====================================
void PassengerController::SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback)
{
	this->callback = callback;
}

//=====================================
// PlaceActor�ɍ��킹�ăp�b�Z���W���[�̎�ނ�؂�ւ��iFieldLevel = World�ł̂ݎg�p�j
//=====================================
void PassengerController::CheckPassengerMesh()
{
	for (auto& model : modelVector)
	{
		// PlaceActor���瑫���̃t�B�[���h�̎�ނ��擾
		int type = continentMap[model->GetFieldPosition()];

		// �t�B�[���h�̃^�C�v�����A�A�N�^�[�̃^�C�v���M�̏ꍇ
		if (type == 0 && model->GetType() == PassengerActor::Ship)
		{
			model->ChangeMesh("Train");
			model->SetType(PassengerActor::Train);
		}
		// �t�B�[���h�̃^�C�v���C�A�A�N�^�[�̃^�C�v���d�Ԃ̏ꍇ
		else if (type == -1 && model->GetType() == PassengerActor::Train)
		{
			model->ChangeMesh("Ship");
			model->SetType(PassengerActor::Ship);
		}
	}
}

//=====================================
// CSV�ǂݍ���
//=====================================
void PassengerController::LoadCSV(const char* path)
{
	if (initializedMap)
		return;

	std::fstream stream(path);

	std::string line;		// �s
	const char Delim = ',';	// ��؂蕶��
	int x = 0;
	int z = 0;

	// �I���܂œǂݍ��ݑ�����
	while (std::getline(stream, line))
	{
		// 1�s���ǂݍ��񂾃f�[�^����؂蕶���ŕ�������
		std::vector<std::string> subStr;
		String::Split(subStr, line, Delim);

		x = 0;

		// ���������f�[�^���Ƃ�map���쐬
		for (auto&& str : subStr)
		{
			int sub = std::stoi(str);
			continentMap.emplace(Field::FieldPosition(x, z), sub);

			x++;
		}
		z++;
	}

	// �s���Ɨ񐔂�ۑ�
	mapRowMax = x;
	mapColumMax = z;

	initializedMap = true;
}

//=====================================
// ���\�[�X�ǂݍ���
//=====================================
void PassengerController::LoadResource()
{
	ResourceManager::Instance()->LoadMesh("Car", "data/MODEL/PassengerActor/ToonCar.x");
	ResourceManager::Instance()->LoadMesh("Train", "data/MODEL/PassengerActor/PassengerTrain.x");
	ResourceManager::Instance()->LoadMesh("Ship", "data/MODEL/PassengerActor/Boat.x");
	ResourceManager::Instance()->LoadMesh("Rocket", "data/MODEL/PassengerActor/PassengerSpace.x");
}

//=====================================
// ��or�C�̃f�[�^��������������ꍇ��������Ăяo��
//=====================================
void PassengerController::RewriteMap(const Field::FieldPosition& pos, const Geography& data)
{
	continentMap[pos] = data;
}