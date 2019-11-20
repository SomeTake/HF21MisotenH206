//=====================================
//
// �K�C�h�J����[GuideCamera.cpp]
// �@�\�F�K�C�h�E�B���h�E�p�J����
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GuideCamera.h"

//=====================================
// �R���X�g���N�^
//=====================================
GuideCamera::GuideCamera()
{
	const float ScreenHeight = 360.0f;
	const float ScreenWidth = 360.0f;
	const float InitViewAspect = ScreenWidth / ScreenHeight;
	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 64.0f, -40.0f);
	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, 64.0f, 0.0f);
	
	transform.SetPosition(InitPos);
	transform.LookAt(InitTarget);

	viewAspect = InitViewAspect;
}

//=====================================
// �f�X�g���N�^
//=====================================
GuideCamera::~GuideCamera()
{
}
