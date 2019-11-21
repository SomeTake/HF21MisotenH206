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
class ResultViewerParam;
class ResultRankingViewer;
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

	//�p�����[�^�󂯎��
	void ReceiveParam(ResultViewerParam&param);

	void SetActive(bool flag);

	std::vector <BaseViewer*> resultViewer;

private:

	ResultRankingViewer * rankingViewer;
	bool isActive;
};

#endif

