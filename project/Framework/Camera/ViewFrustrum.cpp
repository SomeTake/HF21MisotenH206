//=====================================
//
//ViewFrustrum.cpp
//�@�\:�J�����̎�����
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ViewFrustrum.h"
#include "Camera.h"

/**************************************
static�����o
***************************************/
const unsigned ViewFrustrum::VertexMax = 8;

/**************************************
�R���X�g���N�^
***************************************/
ViewFrustrum::ViewFrustrum()
{
	vertexPos.resize(VertexMax, Vector3::Zero);
}

/**************************************
�f�X�g���N�^
***************************************/
ViewFrustrum::~ViewFrustrum()
{
	vertexPos.clear();
}

/**************************************
������̖ʂ̖@���擾����
***************************************/
D3DXVECTOR3 ViewFrustrum::GetNormal(Surface surfaceID)
{
	D3DXVECTOR3 normal = Vector3::Up;
	switch (surfaceID)
	{
	case ViewFrustrum::Left:
		normal = _GetNormal(NearLeftTop, FarLeftTop, NearLeftBottom);
		break;

	case ViewFrustrum::Right:
		normal = _GetNormal(NearRightBottom, FarRightBottom, NearRightTop);
		break;

	case ViewFrustrum::Top:
		normal = _GetNormal(NearLeftTop, NearRightTop, FarLeftTop);
		break;

	case ViewFrustrum::Bottom:
		normal = _GetNormal(NearLeftBottom, FarLeftBottom, NearRightBottom);
		break;
	}

	return normal;
}

/**************************************
���_�ݒ菈��
***************************************/
void ViewFrustrum::SetVertex(const D3DXVECTOR3 & NearLeftTop, const D3DXVECTOR3 & NearRightTop, const D3DXVECTOR3 & NearLeftBottom, const D3DXVECTOR3 & NearRightBottom, const D3DXVECTOR3 & FarLeftTop, const D3DXVECTOR3 & FarRightTop, const D3DXVECTOR3 & FarLeftBottom, const D3DXVECTOR3 & FarRightBottom)
{
	vertexPos[Vertex::NearLeftTop] = NearLeftTop;
	vertexPos[Vertex::NearRightTop] = NearRightTop;
	vertexPos[Vertex::NearLeftBottom] = NearLeftBottom;
	vertexPos[Vertex::NearRightBottom] = NearRightBottom;
	vertexPos[Vertex::FarLeftTop] = FarLeftTop;
	vertexPos[Vertex::FarRightTop] = FarRightTop;
	vertexPos[Vertex::FarLeftBottom] = FarLeftBottom;
	vertexPos[Vertex::FarRightBottom] = FarRightBottom;

}

/**************************************
�@���擾�����i���������j
***************************************/
D3DXVECTOR3 ViewFrustrum::_GetNormal(int v1, int v2, int v3)
{
	return Vector3::Axis(vertexPos[v2] - vertexPos[v1], vertexPos[v3] - vertexPos[v1]);
}

/**************************************
�ʏ�̂����_������
***************************************/
D3DXVECTOR3 ViewFrustrum::GetSurfacePoint(Surface surfaceID)
{
	D3DXVECTOR3 ret = Vector3::Zero;
	switch (surfaceID)
	{
	case Left:
		ret = vertexPos[NearLeftTop];
		break;
	case Right:
		ret = vertexPos[NearRightTop];
		break;
	case Top:
		ret = vertexPos[NearLeftTop];
		break;
	case Bottom:
		ret = vertexPos[FarLeftBottom];
		break;
	default:
		break;
	}

	return ret;
}

/**************************************
������J�����O
***************************************/
bool ViewFrustrum::CheckOnCamera(const D3DXVECTOR3 pos, const float size)
{
	bool ret = false;

	// �J�����̏œ_����`�F�b�N������W���Z�o
	D3DXVECTOR3 target = Camera::MainCamera()->GetTarget();
	D3DXVECTOR3 obj = pos;
	D3DXVECTOR3 side = pos;
	// �œ_�̍���
	if (obj.x < target.x && obj.z < target.z)
	{
		obj.x += size;
		obj.z += size;
		side.x += size;
	}
	// �œ_�̉E��
	else if (obj.x >= target.x && obj.z < target.z)
	{
		obj.x -= size;
		obj.z += size;
		side.x -= size;
	}
	// �œ_�̍���
	else if (obj.x < target.x && obj.z >= target.z)
	{
		obj.x += size;
		obj.z -= size;
		side.x += size;
	}
	// �œ_�̉E��
	else if (obj.x >= target.x && obj.z >= target.z)
	{
		obj.x -= size;
		obj.z -= size;
		side.x -= size;
	}

	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR3 nor = GetNormal(Surface(i));
		D3DXVECTOR3 vec1 = obj - GetSurfacePoint(Surface(i));
		D3DXVECTOR3 vec2 = side - GetSurfacePoint(Surface(i));

		// ������̖@���ƁA�����䂩��I�u�W�F�N�g�ւ̃x�N�g��������όv�Z
		float dot1 = D3DXVec3Dot(&nor, &vec1);
		float dot2 = D3DXVec3Dot(&nor, &vec2);

		// �ǂ��炩�Е�����ʓ��ɂ����OK
		if (dot1 > 0 || dot2 > 0)
		{
			ret = true;
		}
		else
		{
			ret = false;
			break;
		}
	}

	return ret;
}