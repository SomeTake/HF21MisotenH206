//=====================================
//
//�p�[�e�B�N���e�X�g�J��������[TestParticleCamera.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TestParticleCamera.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
TestParticleCamera::TestParticleCamera()
{	
	//�p�����[�^�ݒ�
	const float CameraAngleXZ = D3DXToRadian(45.0f);
	const float CameraAngleY = D3DXToRadian(60.0f);
	const float CameraLength = 50.0f;

	const D3DXVECTOR3 InitPos = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	transform.SetPosition(InitPos);
}
