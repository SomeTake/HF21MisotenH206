//=====================================
//
// ModelViewCamera.h
// �@�\:���f���r���[�J����
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MODELVIEWCAMERA_H_
#define _MODELVIEWCAMERA_H_

#include "../../main.h"
#include "../../Framework/Camera/Camera.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class ModelViewCamera : public Camera
{
	using Camera::Camera;
public:
	ModelViewCamera();
	
	void Update() override;
};

#endif