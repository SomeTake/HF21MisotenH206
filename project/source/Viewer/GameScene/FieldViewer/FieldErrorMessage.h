
//=============================================================================
//
// �C�x���g�e���b�v���� [FieldErrorMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _FIELD_ERRO_MESSAGE_H_
#define _FIELD_ERRO_MESSAGE_H_

#include "../../Framework/BaseViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include <vector>
#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FieldErrorMessage :public BaseViewer
{
public:
	FieldErrorMessage();
	~FieldErrorMessage();

	//�e���b�v�̎��
	enum ErroID
	{
		//�X�^���ƂȂ����Ă��܂���
		NotConnection,
		//�X�g�b�N������܂���
		StockShortage,
		//���Ƌ��͌q�����܂���
		BridgeConnection,
		//���̓J�[�u�ɂł��܂���
		CurveBridge,
		//��ސ�
		Max
	};

	void Update();
	void Draw(void);
	void Set(ErroID id);

private:
	BaseViewerDrawer *text;

	//�Đ�
	void Play();

	//�e�N�X�`�����󂯓n��
	void PassTexture(ErroID id);

	//�Đ������ǂ���
	bool isPlaying;

	//�t���[���J�E���g
	int countFrame;
};

#endif