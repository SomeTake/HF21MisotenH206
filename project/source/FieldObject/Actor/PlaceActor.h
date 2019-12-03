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
#include "../../Field/FieldConfig.h"

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
	PlaceActor();
	virtual ~PlaceActor();

	virtual void Init(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// �C���^�[�t�F�[�X
	virtual void Rotate(float y);								// Y����]
	void SetPosition(const D3DXVECTOR3&pos);			// ���W�Z�b�g
	void SetColor(const D3DXCOLOR& color);	// ���b�V���̐F�ύX
	void ResetTransform();								// ���W�A��]�A�傫�������Z�b�g����

	static const D3DXVECTOR3 SizeCullingBox;			//������J�����O�Ɏg�p����{�b�N�X�̑傫��

protected:
	// ***�p����̃N���X�œǂݍ���***
	MeshContainer* mesh;								// ���b�V���R���e�i
	Field::Model::PlaceType type;								// �A�N�^�[�̎��
	// ******************************

	bool onCamera;										// �`��̉۔���

private:
	static const D3DXVECTOR3 Scale;

#if _DEBUG
	void Debug();
#endif
};

#endif
