//=============================================================================
//
// ���S�̃����N���x���㏸�C�x���g�N���X [AllLinkLevelUpEvent.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "AllLinkLevelUpEvent.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../../Framework/Sound/SoundEffect.h"
#include "../../Sound/SoundConfig.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const int LinkLevelUpNum = 1;
const std::string AllLinkLevelUpEvent::CityMessage[] = {
	{"�䕗�̔�Q�Ȃ��I\n�앨�̎��n�ʂ�200%�ɁI�I"},
	{"�i����ǂɐ����I\n���B�����u�����āv���a���I"},
	{"���ɓK�����y��𔭌��I\n���n�ʂ��{���I"}
};
const std::string AllLinkLevelUpEvent::WorldMessage[] = {
	{"�I�����s�b�N���J�Â��ꂽ�I\n�e�n�ŐV�����q�[���[�̒a�����I"},
	{"���j�I��ɂ�閼���a���I\n�u�}�W�C���������v"},
	{"�I�肽���������_�����l���I\n���̊��C�㏸�I�I"}
};
const std::string AllLinkLevelUpEvent::SpaceMessage[] = {
	{"�߂�����f������F���H���J������ăn�b�s�[�I"},
	{"�V�f���̐V�H�ނŐV�F���H���ł����I�V���o�I�I"},
	{"�~�V���������F�I�H\n�O�c���F���H��僌�X�g�����a���I�I"}
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
AllLinkLevelUpEvent::AllLinkLevelUpEvent() :
	EventBase(false)
{
	GuideViewer::Instance()->SetData("�S�Ă̒��̃����N���x�����㏸",
		GuideActor::AnimState::FistPump,
		SoundConfig::AllLinkLevelUp);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
AllLinkLevelUpEvent::~AllLinkLevelUpEvent()
{

}

//=============================================================================
// �X�V
//=============================================================================
void AllLinkLevelUpEvent::Update()
{
	fieldEventHandler->AdjustAllLinkLevel(LinkLevelUpNum);
	UseFlag = false;
}

//=============================================================================
// �`��
//=============================================================================
void AllLinkLevelUpEvent::Draw()
{

}

//=============================================================================
// �C�x���g���b�Z�[�W���擾
//=============================================================================
string AllLinkLevelUpEvent::GetEventMessage(int FieldLevel)
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
