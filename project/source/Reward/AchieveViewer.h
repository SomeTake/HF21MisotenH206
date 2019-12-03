//=====================================
//
// �A�`�[�u�r���A�[[AchieveViewer.h]
// �@�\�F�����[�h��B�������Ƃ��ɒʒB���s���r���A�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _ACHIEVEVIEWER_H_
#define _ACHIEVEVIEWER_H_

#include "../../Framework/Renderer2D/Polygon2D.h"

//**************************************
// �N���X��`
//**************************************
class AchieveViewer
{
private:
	Polygon2D* polygon;
	int index;					// �g�p����e�N�X�`���ԍ�
	bool active;
	int cntFrame;
	D3DXVECTOR3 movePosition;

	static const int DivideX;
	static const int DivideY;
	static const float SizeX;
	static const float SizeY;
	static const float MoveValue;
	static const D3DXVECTOR3 InitPosition;

public:
	AchieveViewer();
	~AchieveViewer();

	void Update();
	void Draw();

	void SetIndex(int index);
	void SetActive();
};

#endif
