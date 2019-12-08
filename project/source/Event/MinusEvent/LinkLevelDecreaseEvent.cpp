//=============================================================================
//
// �����N���x�������C�x���g�N���X [LinkLevelDecreaseEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "LinkLevelDecreaseEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const int LinkLevelDecreaseNum = -1;
const std::string LinkLevelDecreaseEvent::CityMessage[] = {
	{"�������̌�5�ԈႦ���I\n�ܖ����������܂ł����I"},
	{"SNS�Ŋg�U���Ă����Ȃ�����I"},
	{"����I�������񂷂�X���I"}
};
const std::string LinkLevelDecreaseEvent::WorldMessage[] = {
	{"�ׂ̍����U�߂Ă����I"},
	{"�����͓������x���̂��̓��m�ł���\n�������Ȃ��I"},
	{"�A�t���J�ł�1���Ԃ�60�b�i��ł��܂�"}
};
const std::string LinkLevelDecreaseEvent::SpaceMessage[] = {
	{"�N��...���O�́I�H"},
	{"�q�[�h�b�y���Q���K�[�l�@�h��"},
	{"���Ȃ��͒N�H���w�̓������H\n���͖₤�I"}
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
LinkLevelDecreaseEvent::LinkLevelDecreaseEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetMessage("�����N���x����������܂���");
	GuideViewer::Instance()->ChangeAnim(GuideActor::AnimState::Surprised);
	SE::Play(SoundConfig::LinkLevelDown, SoundConfig::VolumeVoice);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
LinkLevelDecreaseEvent::~LinkLevelDecreaseEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void LinkLevelDecreaseEvent::Update()
{
	fieldEventHandler->AdjustAllLinkLevel(LinkLevelDecreaseNum);
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void LinkLevelDecreaseEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string LinkLevelDecreaseEvent::GetEventMessage(int FieldLevel)
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
