//=====================================
//
// �r���[�t���X�^���{�b�N�X[ViewFrustumBox.h]
// �@�\�F������J�����O�p�{�b�N�X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _VIEWFRUSTUMBOX_H_
#define _VIEWFRUSTUMBOX_H_

#include "../../../main.h"

//**************************************
// �N���X��`
//**************************************
class ViewFrustumBox
{
public:
	enum Point
	{
		UpLeftFar,
		UpRightFar,
		UpLeftNear,
		UpRightNear,
		DownLeftFar,
		DownRightFar,
		DownLeftNear,
		DownRightNear,
		Max
	};

	ViewFrustumBox(const D3DXVECTOR3 pos, float size);
	~ViewFrustumBox();

	// �Ώۂɍł��߂��A�������W���擾����
	D3DXVECTOR3 SearchNearPoint(const D3DXVECTOR3 target);
	D3DXVECTOR3 SearchFarPoint(const D3DXVECTOR3 target);

	static const float PlaceActorSize;
	static const float PassengerActorSize;

private:
	D3DXVECTOR3 pos;				// ����W
	D3DXVECTOR3 point[Point::Max];	// 8���_
};

#endif
