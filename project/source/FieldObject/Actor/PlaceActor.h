//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.h]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PLACEACTOR_H_
#define _PLACEACTOR_H_

#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Math/Easing.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../Field/Place/PlaceConfig.h"
#include "../../../Framework/Pattern/BaseState.h"

//**************************************
// �}�N����`
//**************************************

//**************************************
// �񋓎q�ݒ�
//**************************************
namespace FModel = Field::Model;

//**************************************
// �N���X��`
//**************************************
class PlaceActor :
	public GameObject
{
public:
	/**************************************
	�A�N�^�[�̃X�e�[�g��\���񋓎q
	***************************************/
	enum State
	{
		Idle,	// �ҋ@
		Create,	// �쐬
		Remove,	// �폜
		Link,	// �����N���x�����オ����
		Max
	};
	using ActorState = BaseState<PlaceActor, State>;

	PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	virtual ~PlaceActor();

	virtual State Update();
	virtual void Draw();

	// �C���^�[�t�F�[�X
	void ChangeState(ActorState *next);					// �A�j���[�V�����Đ��i�Đ�������Ƃ��̂݌Ăяo���j
	void Rotate(float y);								// Y����]
	void SetColor(const D3DXCOLOR& color, UINT index);	// ���b�V���̐F�ύX

protected:
	// ***�p����̃N���X�œǂݍ���***
	MeshContainer* mesh;				// ���b�V���R���e�i
	// ******************************

	ActorState *state;					// ���݂̃X�e�[�g
	int cntState;						// �X�e�[�g���ł̌��݃t���[���̃J�E���g�Ɏg�p

private:
	static const D3DXVECTOR3 ActorScale;

	// �X�e�[�g�̑O���錾
	class IdleActorState;
	class CreateActorState;
	class RemoveActorState;
	class LinkActorState;
};

#endif
