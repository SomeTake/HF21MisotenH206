//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.h]
// �@�\�F�t�B�[���h��ɐݒu����钬�⓹�A�Ȃǂ�3D�I�u�W�F�N�g
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PLACEACTOR_H_
#define _PLACEACTOR_H_

#include "Framework/Core/GameObject.h"
#include "Framework/Renderer3D/MeshContainer.h"
#include "Framework/Math/Easing.h"
//**************************************
// �}�N����`
//**************************************

//**************************************
// �v���C�X�A�N�^�[�p���N���X
//**************************************
class PlaceActor :
	public GameObject
{
protected:
	MeshContainer* container;					// ���b�V���R���e�i
	int animType;								// �A�j���[�V�����̎��
	EaseType easeType;							// �C�[�W���O�^�C�v

	virtual void PlayAnimation(int AnimType);	// �A�j���[�V�����Đ�
	virtual void Rotate(float y);				// Y����]

public:
	PlaceActor(const D3DXVECTOR3& pos);
	virtual ~PlaceActor();

	virtual void Update();
	virtual void Draw();
};

#endif
