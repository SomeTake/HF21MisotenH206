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
	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, 10.0f, 100.0f);
	
	transform->SetPosition(InitPos);
	transform->LookAt(InitTarget);

	viewAspect = InitViewAspect;

	D3DXMatrixIdentity(&viewport);
	viewport._11 = ScreenWidth / 2.0f;
	viewport._22 = -ScreenHeight / 2.0f;
	viewport._41 = ScreenWidth / 2.0f;
	viewport._42 = ScreenHeight / 2.0f;

	//�r���[�s��쐬
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view,
		&InitPos,
		&InitTarget,
		&transform.Up());

	//�v���W�F�N�V�����s��쐬
	D3DXMatrixIdentity(&projection);
	D3DXMatrixPerspectiveFovLH(&projection,
		viewAngle,
		viewAspect,
		viewNear,
		viewFar);

	//�ϊ��s����v�Z
	VPV = view * projection * viewport;

	//�t�s����v�Z
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixInverse(&invProjection, NULL, &projection);
	D3DXMatrixInverse(&invVPV, NULL, &VPV);

	Set();
}

//=====================================
// �f�X�g���N�^
//=====================================
GuideCamera::~GuideCamera()
{
}

void GuideCamera::Update(void)
{
	D3DXVECTOR3 eyePosition = transform.GetPosition();
	D3DXVECTOR3 targetPosition = D3DXVECTOR3(0.0f, 10.0f, 100.0f);
	D3DXVECTOR3 upVector = transform.Up();

	//�r���[�s��쐬
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view,
		&eyePosition,
		&targetPosition,
		&upVector);

	//�v���W�F�N�V�����s��쐬
	D3DXMatrixIdentity(&projection);
	D3DXMatrixPerspectiveFovLH(&projection,
		viewAngle,
		viewAspect,
		viewNear,
		viewFar);

	//�ϊ��s����v�Z
	VPV = view * projection * viewport;

	//�t�s����v�Z
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixInverse(&invProjection, NULL, &projection);
	D3DXMatrixInverse(&invVPV, NULL, &VPV);

	//������v�Z
	CalculateFrustrum();
}

D3DXVECTOR3 GuideCamera::UnProjection(const D3DXVECTOR3 & pos, float z) const
{
	D3DXVECTOR3 out;
	D3DXVec3TransformCoord(&out, &D3DXVECTOR3(pos.x, pos.y, z), &invVPV);
	return out;
}
