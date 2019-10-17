//=============================================================================
//
// �C�x���g�R���g���[���[�N���X [EventController.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "EventController.h"
#include "EventConfig.h"
#include "MinusEvent/CityDestroyEvent.h"

#include "../../Framework/Core/Utility.h"
#include "../../Framework/String/String.h"

#include <fstream>
#include <string>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �g�p���Ă��Ȃ��C�x���g���폜
//bool RemoveCondition(EventBase *Event) { return !Event->GetUse(); }
bool RemoveCondition(EventBase *Event) { return Event == NULL ? true : false; }

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************



//=============================================================================
// �R���X�g���N�^
//=============================================================================
EventController::EventController(int FieldLevel) : FieldLevel(FieldLevel)
{
	//LoadCSV("data/FIELD/sample01_Event.csv");

	EventVec.push_back(new CityDestroyEvent(FieldLevel, D3DXVECTOR3(150.0f, 0.0f, 150.0f)));

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
EventController::~EventController()
{
	// �C�x���g�x�N�g���폜
	Utility::DeleteContainer(EventVec);
}

//=============================================================================
// �X�V
//=============================================================================
void EventController::Update()
{
	for (auto &Event : EventVec)
	{
		if (Event->GetUse())
		{
			Event->Update();
		}
		else
		{
			SAFE_DELETE(Event);
		}
	}

	EventVec.erase(std::remove_if(std::begin(EventVec), std::end(EventVec), RemoveCondition), std::end(EventVec));
}

//=============================================================================
// �`��
//=============================================================================
void EventController::Draw()
{
	for (auto &Event : EventVec)
	{
		Event->Draw();
	}
}

//=============================================================================
// CSV�̓ǂݍ���
//=============================================================================
void EventController::LoadCSV(const char* FilePath)
{
	//�������ς݂ł���΃��^�[��
	//if (initialized)
	//	return;

	//CSV�t�@�C����ǂݍ���
	std::ifstream stream(FilePath);

	std::string line;			// CSV��1�s���ǂރo�b�t�@
	const char Delim = ',';		// ��؂蕶��
	int x = 0;					// Event��X�ʒu
	int z = 0;					// Event��Z�ʒu

	//CSV�̏I���܂œǂݍ��ݑ�����
	while (std::getline(stream, line))
	{
		//1�s���ǂݍ��񂾃f�[�^����؂蕶���ŕ�������
		std::vector<std::string> subStr;
		String::Split(subStr, line, Delim);

		x = 0;

		for (auto &str : subStr)
		{
			int Type = std::stoi(str);
			// 
			if (Type != EventConfig::NoEvent)
			{
				EventCSVData.push_back(EventInfo{ x, z, Type });
			}
			x++;
		}
		z++;
	}

	//����������
	//initialized = true;
}

//=============================================================================
// �C�x���g�����̊m�F
//=============================================================================
void EventController::ReceiveEvent(void)
{

}
