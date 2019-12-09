//=====================================
//
//SpaceGrid.h
//�@�\:�F�����x���̃O���b�h
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPACEGRID_H_
#define _SPACEGRID_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class BoardPolygon;
class SpaceGridEffect;

/**************************************
�N���X��`
***************************************/
class SpaceGrid : GameObject
{
public:
	SpaceGrid();
	virtual ~SpaceGrid();

	void Update();
	void Draw();

	const static int PeriodFade;

private:
	BoardPolygon * polygon;
	SpaceGridEffect *effect;
	int cntFrame;
};
#endif