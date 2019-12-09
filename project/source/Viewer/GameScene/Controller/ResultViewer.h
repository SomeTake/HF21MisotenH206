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
class ResultViewerParam;
class BaseViewer;
class GuideActor;
class SubScreen;
class Camera;

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

private:
	std::vector <BaseViewer*> resultViewer;
	ResultScoreViewer * scoreViewer;
	ResultViewerParam *viewerParam;

	bool isActive;

	//��ʉE�ɕ\�����郍�{
	GuideActor* actor;

	//���{��`�悷�郌���_�����O�^�[�Q�b�g
	SubScreen* screen;

	//���{�`��p�̃J����
	Camera *camera;
};

#endif

