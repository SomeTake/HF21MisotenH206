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
#include "../Field/Place/PlaceConfig.h"
//**************************************
// �}�N����`
//**************************************

//**************************************
// �񋓎q�ݒ�
//**************************************
namespace FModel = Field::Model;
namespace Field::Actor
{
	/**************************************
	�A�N�^�[�̃A�j���[�V�����^�C�v��\���񋓎q
	***************************************/
	enum AnimType
	{
		Create,
		Remove,
		AnimMax
	};
}
namespace FActor = Field::Actor;

//**************************************
// �N���X��`
//**************************************
class PlaceActor :
	public GameObject
{
protected:
	// ***�p����̃N���X�œǂݍ���***
	MeshContainer* mesh;				// ���b�V���R���e�i
	// ******************************
	FActor::AnimType animType;			// �A�j���[�V�����̎��
	bool animActive;					// �A�j���[�V�����Đ����t���O

public:
	PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	virtual ~PlaceActor();

	virtual void Update();
	virtual void Draw();

	// �C���^�[�t�F�[�X
	virtual void PlayAnimation(FActor::AnimType AnimType);	// �A�j���[�V�����Đ��i�Đ�������Ƃ��̂݌Ăяo���j
	void Rotate(float y);									// Y����]
	void SetColor(const D3DXCOLOR& color, UINT index);		// ���b�V���̐F�ύX

private:
	static const D3DXVECTOR3 ActorScale;
};

#endif
