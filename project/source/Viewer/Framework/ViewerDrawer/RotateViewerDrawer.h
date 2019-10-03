//=============================================================================
//
// ��]�r���A�[�`��p���� [RotateViewerDrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _ROTATE_VIEWER_DRAWER_H_
#define _ROTATE_VIEWER_DRAWER_H_

#include "source/Viewer/Framework/ViewerDrawer/BaseViewerDrawer.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RotateViewerDrawer :public BaseViewerDrawer
{
public:
	void CreateCircle();
	void MakeVertex();
	void SetVertex();

	float baseAngle;
	float radius;
};

#endif

