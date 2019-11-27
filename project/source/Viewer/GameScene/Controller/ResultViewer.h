//=============================================================================
//
// ���ʃr���A�[�R���g���[������ [ResultViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_VIEWER_H_
#define _RESULT_VIEWER_H_

#include <vector>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class ResultScoreViewer;
class ResultNameEntryViewer;
class ResultViewerParam;
class BaseViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultViewer
{
public:
	ResultViewer();
	~ResultViewer();

	void Update(void);
	void Draw(void);

	//�A�N�e�B�u��Ԃ��Z�b�g
	void SetActive(bool flag);

	//�p�����[�^�̎󂯎�菈��
	void ReceiveParam(int cityScore,int worldScore,int spaceScore);

	//�o�^���擾����
	std::string GetEntryName(void);

private:
	std::vector <BaseViewer*> resultViewer;
	ResultScoreViewer * scoreViewer;
	ResultNameEntryViewer *nemeEntryViewer;
	ResultViewerParam *viewerParam;

	bool isActive;
};

#endif

