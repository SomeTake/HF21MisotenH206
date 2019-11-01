//=============================================================================
//
// AI���x���r���A�[���� [LevelViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LEVEL_VIEWER_H_
#define _LEVEL_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include <vector>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CountViewerDrawer;
class CircleGauge;
class BaseViewerDrawer;
class RotateViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LevelViewer :public BaseViewer
{
public:
	LevelViewer();
	~LevelViewer();

	void Update(void);
	void Draw(void);

	//����ID
	enum ArrowID
	{
		LevelUp,
		LevelDown,
	};

	//AI���x���r���A�[�̎��
	enum StockViewerType
	{
		LevelAI,
		RatioLevel,
	};

	//AI���x���r���A�[�̎�ސ�
	static const int typeMax = 2;

	//�p�����[�^���󂯂Ƃ锠
	float parameterBox[typeMax];

private:

	//�~�Q�[�W
	CircleGauge *circleGuage;

	//����
	CountViewerDrawer *num;

	//�w�i
	BaseViewerDrawer *bg;

	//���
	RotateViewerDrawer *arrow;

	//���̃e�N�X�`�����R���e�i
	std::vector <LPDIRECT3DTEXTURE9> arrowTexContainer;

	//�����z�b�s���O����
	void HopNumber(void);

	//�`��pratioLevel�ݒ�
	void SetDrawingRatioLevel(void);

	//�`��pratioLevel����
	void IncreaseDrawingRatioLevel(void);

	//�`��pratioLevel����
	void DecreaseDrawingRatioLevel(void);

	//���̃e�N�X�`�����󂯓n��
	void PassArrowTexture(ArrowID id);

	//���̃Z�b�g����
	void SetArrow(ArrowID id);

	//���̏㉺����
	void UpDownArrow();

	//���݂̃p�����[�^
	int currentParam[typeMax];

	//�P�t���[���O�̃p�����[�^
	int lastParam[typeMax];

	//�`��pratioLevel
	float drawingRatioLevel;

	//LevelAI�����������ǂ���
	bool isLevelAI_Increasing;

	//LevelAI�����������ǂ���
	bool isLevelAI_Decreasing;

	//��󂪍Đ������ǂ���
	bool isArrowPlaying;

	//���㉺�����p�̃��W�A��
	float radian = 0.0f;
};

#endif