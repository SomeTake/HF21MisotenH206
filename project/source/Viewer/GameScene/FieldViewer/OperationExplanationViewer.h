//=============================================================================
//
// ��������r���[�A���� [OperationExplanationViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _OPERATION_EXPLANATION_VIEWER_H_
#define _OPERATION_EXPLANATION_VIEWER_H_

#include "../../Framework/BaseViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class OperationExplanationViewer :public BaseViewer
{
public:
	OperationExplanationViewer();
	~OperationExplanationViewer();

	//�I�y���[�V�����̎��
	enum OperationID
	{
		//Z�ɂ��āu�������v��\������
		Z_Build,
		//Z�ɂ��āu�L�����Z���v��\������
		Z_Cancel,
		//X�ɂ��āu�J�񂷂�v��\������
		X_Develop,
		//X�ɂ��āu�L�����Z���v��\������
		X_Cancel,
		//Space�ɂ��āu���_�ύX�v��\������
		C_Change,
		//�u���߂�v
		FarView,
		// �u�߂�v
		NearView,
		//Z�ɂ��Ă̑����\�����Ȃ�
		Z_None,
		//X�ɂ��Ă̑����\�����Ȃ�
		X_None,
		//Space�ɂ��Ă̑����\�����Ȃ�
		C_None,
		//��ސ�
		Max
	};

	void Update();
	void Draw(void);
	void Set(OperationID id0, OperationID id1, OperationID id2, OperationID id3);

	void SetActive(bool state);

private:

	const static int textMax = 4;

	//�e�L�X�g
	BaseViewerDrawer * text[textMax];

	bool active;

	//�e�N�X�`��UV�Z�b�g����
	void SetTexture(OperationID id0, OperationID id1, OperationID id2, OperationID id3);
};

#endif