
//=============================================================================
//
// �t�B�[���h�G���[���b�Z�[�W���� [FieldErrorMessage.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _FIELD_ERRO_MESSAGE_H_
#define _FIELD_ERRO_MESSAGE_H_

#include "../../Framework/BaseViewer.h"

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

	//���b�Z�[�W�̎��
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

	//�e�L�X�g
	BaseViewerDrawer *text;

	//�Đ�
	void Play();

	//�e�N�X�`�����󂯓n��
	void SetTexture(ErroID id);

	//�Đ������ǂ���
	bool isPlaying;

	//�t���[���J�E���g
	int countFrame;
};

#endif