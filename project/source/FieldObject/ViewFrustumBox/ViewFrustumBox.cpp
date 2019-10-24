//=====================================
//
// �r���[�t���X�g�����{�b�N�X[ViewFrustrumBox.h]
// �@�\�F������J�����O�p�{�b�N�X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "ViewFrustumBox.h"
#include <vector>
#include <algorithm>

//**************************************
// �����o�ϐ�������
//**************************************
const float ViewFrustumBox::PlaceActorSize = 5.0f;
const float ViewFrustumBox::PassengerActorSize = 3.0f;

//=====================================
// �R���X�g���N�^
//=====================================
ViewFrustumBox::ViewFrustumBox(const D3DXVECTOR3 pos, float size) :
	pos(pos)
{
	this->point[UpLeftFar] = this->pos + D3DXVECTOR3(-size, size, -size);
	this->point[UpRightFar] = this->pos + D3DXVECTOR3(size, size, -size);
	this->point[UpLeftNear] = this->pos + D3DXVECTOR3(-size, size, size);
	this->point[UpRightNear] = this->pos + D3DXVECTOR3(size, size, size);
	this->point[DownLeftFar] = this->pos + D3DXVECTOR3(-size, -size, -size);
	this->point[DownRightFar] = this->pos + D3DXVECTOR3(size, -size, -size);
	this->point[DownLeftNear] = this->pos + D3DXVECTOR3(-size, -size, size);
	this->point[DownRightNear] = this->pos + D3DXVECTOR3(size, -size, size);
}

//=====================================
// �f�X�g���N�^
//=====================================
ViewFrustumBox::~ViewFrustumBox()
{
}

//=====================================
// �Ώۂ���ŒZ�����̍��W���擾����
//=====================================
D3DXVECTOR3 ViewFrustumBox::SearchNearPoint(const D3DXVECTOR3 target)
{
	// �Ώۂ�����W�ւ̋������v�Z
	std::vector<float> dist;
	dist.reserve(Point::Max);
	for (int i = 0; i < Point::Max; i++)
	{
		dist.push_back(D3DXVec3LengthSq(&(point[Point(i)] - target)));
	}

	// �ŏ��l�̓Y�����擾
	std::vector<float>::iterator minIt = std::min_element(dist.begin(), dist.end());
	size_t minIndex = std::distance(dist.begin(), minIt);

	return point[minIndex];
}

//=====================================
// �Ώۂ���Œ������̍��W���擾����
//=====================================
D3DXVECTOR3 ViewFrustumBox::SearchFarPoint(const D3DXVECTOR3 target)
{
	// �Ώۂ�����W�ւ̋������v�Z
	std::vector<float> dist;
	dist.reserve(Point::Max);
	for (int i = 0; i < Point::Max; i++)
	{
		dist.push_back(D3DXVec3LengthSq(&(point[Point(i)] - target)));
	}

	// �ő�l�̓Y�����擾
	std::vector<float>::iterator maxIt = std::max_element(dist.begin(), dist.end());
	size_t maxIndex = std::distance(dist.begin(), maxIt);

	return point[maxIndex];
}
