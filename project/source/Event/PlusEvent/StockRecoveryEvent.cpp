//=============================================================================
//
// �X�g�b�N�񐔉񕜃C�x���g�N���X [StockRecoveryEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "StockRecoveryEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const int AddNum = 3;
const std::string StockRecoveryEvent::CityMessage[] = {
	{"�Ղ肾���b�V���C�I"},
	{"�^�s�I�J�����Ղ�I\n�����݂͂�ȂŃ^�s�낤�I"},
	{"�˓I�Ōi�i�Q�b�g�I"}
};
const std::string StockRecoveryEvent::WorldMessage[] = {
	{"���납��̂̋��݂��U�b�N�U�N�I"},
	{"�C�������ɍ��l�ɖ��߂��Ă���Ȃ񂩏o�Ă����I"},
	{"����ȂƂ���ɋ��B���₪����..."}
};
const std::string StockRecoveryEvent::SpaceMessage[] = {
	{"�ӂƋ�����グ���琯���Y�킾����"},
	{"�����I���ꐯ�I"},
	{"�y�K�T�X�������I�I"}
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
StockRecoveryEvent::StockRecoveryEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetData("�h�����̃X�g�b�N����",
		GuideActor::AnimState::Cheering,
		SoundConfig::StockRecovery);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
StockRecoveryEvent::~StockRecoveryEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void StockRecoveryEvent::Update()
{
	fieldEventHandler->AddStockNum(AddNum);
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void StockRecoveryEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string StockRecoveryEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	int r = rand() % 3;
	if (FieldLevel == Field::City)
	{
		MessageContainer.push_back(CityMessage[r]);
	}
	else if (FieldLevel == Field::World)
	{
		MessageContainer.push_back(WorldMessage[r]);
	}
	else if (FieldLevel == Field::Space)
	{
		MessageContainer.push_back(SpaceMessage[r]);
	}

	if (!MessageContainer.empty())
	{
		int MessageNo = rand() % MessageContainer.size();
		return MessageContainer.at(MessageNo);
	}
	else
	{
		string ErrMsg = "�C�x���g���b�Z�[�W������܂���";
		return ErrMsg;
	}
}
