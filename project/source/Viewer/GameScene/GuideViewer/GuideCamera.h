//=====================================
//
// �K�C�h�J����[GuideCamera.h]
// �@�\�F�K�C�h�E�B���h�E�p�J����
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GUIDECAMERA_H_
#define _SUIDECAMERA_H_

#include "../../../../Framework/Camera/Camera.h"

//**************************************
// �N���X��`
//**************************************
class GuideCamera :
	public Camera
{
private:
public:
	GuideCamera();
	~GuideCamera();
	D3DXVECTOR3 UnProjection(const D3DXVECTOR3 & pos, float z) const override;
};

#endif