//=====================================
//
// �Z���N�g�J����[SelectCamera.h]
// �@�\�F�Z���N�g�E�B���h�E�p�J����
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "SelectCamera.h"

//=====================================
// �R���X�g���N�^
//=====================================
SelectCamera::SelectCamera()
{
	const float ScreenHeight = 320.0f;
	const float ScreenWidth = 1200.0f;
	const float InitViewAspect = ScreenWidth / ScreenHeight;
	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 10.0f, -100.0f);
	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, -30.0f, 0.0f);

	transform.SetPosition(InitPos);
	transform.LookAt(InitTarget);

	viewAspect = InitViewAspect;
}

//=====================================
// �f�X�g���N�^
//=====================================
SelectCamera::~SelectCamera()
{
}
