//=============================================================================
//
// �����N���x���㏸�C�x���g�N���X [LinkLevelUpEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "LinkLevelUpEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const int LinkLevelUpNum = 1;
const std::string LinkLevelUpEvent::message[] = {
	{"�ƂȂ�̒�����H�ו��������Ă��đ�u�[���I"},
	{"���Z������V���Ȍ��N�@�̓`���I\n�������L�т�炵��..."},
	{"�F���l�����I\n�l�ނɐV���ȋZ�p�I�I"}
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
LinkLevelUpEvent::LinkLevelUpEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetMessage("���̃����N���x�����㏸���܂���");
	GuideViewer::Instance()->ChangeAnim(GuideActor::AnimState::FistPump);
	SE::Play(SE::VoiceType::LinkLevelUp, 1.0);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
LinkLevelUpEvent::~LinkLevelUpEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void LinkLevelUpEvent::Update()
{
	fieldEventHandler->AdjustAllLinkLevel(LinkLevelUpNum);
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void LinkLevelUpEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string LinkLevelUpEvent::GetEventMessage(int FieldLevel)
{
	vector<string> MessageContainer;

	int r = rand() % 3;
	MessageContainer.push_back(message[r]);

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
