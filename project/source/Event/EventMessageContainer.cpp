//=============================================================================
//
// �C�x���g���b�Z�[�W�R���e�i�N���X [EventMessageContainer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "EventMessageContainer.h"
#include "EventConfig.h"
#include "../Field/Place/PlaceConfig.h"

using namespace EventConfig;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
EventMessageContainer::EventMessageContainer()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
EventMessageContainer::~EventMessageContainer()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
void EventMessageContainer::GetEventMessage(int FieldLevel, int EventType, const char** MessagePtr)
{
	std::vector<const char*>MessageContainer;

	switch (EventType)
	{
		// ============================
		// ���̔��W���x���㏸
		// ============================
	case CityLevelUp:

		if (FieldLevel == Field::Model::City)
		{
			MessageContainer.push_back("�C�x���g���b�Z�[�W1");
			MessageContainer.push_back("�C�x���g���b�Z�[�W2");
			MessageContainer.push_back("�C�x���g���b�Z�[�W3");
			MessageContainer.push_back("�C�x���g���b�Z�[�W4");
			MessageContainer.push_back("�C�x���g���b�Z�[�W5");
		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// �V�������A���A���o��
		// ============================
	case NewCity:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// ����ȃ`�b�v�̎g�p�񐔉�
		// ============================
	case ChipRecovery:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// ���Ɂu�L���l�������ԁv�t�^�B���b�Ԕ��W�X�s�[�h�㏸
		// ============================
	case FamousPeople:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// �S�̂Ƀ{�[�i�X�A����̒��ɍX�Ƀ{�[�i�X
		// ============================
	case Bonus:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// �X���b�g���񂵂�AI���W���x���Ƀ{�[�i�X
		// ============================
	case AILevelUp:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// ���̔��W���x������
		// ============================
	case CityLevelDecrease:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// ������
		// ============================
	case CityDestroy:

		if (FieldLevel == Field::Model::City)
		{
			MessageContainer.push_back("�����ŃC�x���g���b�Z�[�W1�Ԃ���I");
			MessageContainer.push_back("�����ŃC�x���g���b�Z�[�W2�Ԃ���I");
			MessageContainer.push_back("�����ŃC�x���g���b�Z�[�W3�Ԃ���I");
		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// AI���W���x������
		// ============================
	case AILevelDecrease:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// ���씽�]�i�㉺���E�j
		// ============================
	case MoveInverse:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// ��莞�ԓ���`�b�v�g�p�s��
		// ============================
	case BanSpecialChip:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

		// ============================
		// �����_�̍��G�x��莞�ԏ㏸
		// ============================
	case CongestionUp:

		if (FieldLevel == Field::Model::City)
		{

		}
		else if (FieldLevel == Field::Model::World)
		{

		}
		else if (FieldLevel == Field::Model::Space)
		{

		}
		break;

	default:
		break;
	}

	if (!MessageContainer.empty())
	{
		int No = rand() % MessageContainer.size();
		*MessagePtr = MessageContainer.at(No);
	}
}


