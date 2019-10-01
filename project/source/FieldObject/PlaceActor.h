//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.h]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PLACEACTOR_H_
#define _PLACEACTOR_H_

#include "../../Framework/Core/GameObject.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class PlaceActor :
	public GameObject
{
protected:
	MeshContainer* mesh;				// ���b�V���R���e�i

	// ***�p����̃N���X�Őݒ�***
	int animType;						// �A�j���[�V�����̎��
	EaseType easeType;					// �C�[�W���O�^�C�v
	// **************************

	void PlayAnimation(int AnimType);	// �A�j���[�V�����Đ�
	void Rotate(float y);				// Y����]

public:
	PlaceActor(const D3DXVECTOR3& pos);
	virtual ~PlaceActor();

	virtual void Update();
	virtual void Draw();
};

#endif
