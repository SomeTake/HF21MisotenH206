//=============================================================================
//
// �C�x���g�R���t�B�O [EventConfig.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EventConfig_H_
#define _EventConfig_H_

namespace EventConfig
{
	enum EventType
	{
		CityLevelUp,		// ���̔��W���x���㏸
		NewCity,			// �V�������A���A���o��
		StockRecovery,		// ���A�h�����̃X�g�b�N���𑝂₷
		FamousPeople,		// ���Ɂu�L���l�������ԁv�t�^�B���b�Ԕ��W�X�s�[�h�㏸
		Bonus,				// �S�̂Ƀ{�[�i�X�A����̒��ɍX�Ƀ{�[�i�X
		AILevelUp,			// �X���b�g���񂵂�AI���W���x���Ƀ{�[�i�X
		CityLevelDecrease,	// ���̔��W���x������
		CityDestroy,		// ������
		AILevelDecrease,	// AI���W���x������
		MoveInverse,		// ���씽�]�i�㉺���E�j
		BanStockUse,		// ��莞�ԓ���`�b�v�g�p�s��
		CongestionUp,		// �����_�̍��G�x��莞�ԏ㏸
		NoEvent = -1,		// �C�x���g�Ȃ�
	};
}

#endif