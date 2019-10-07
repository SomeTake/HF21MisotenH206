//=====================================
//
// �p�b�Z���W���[�A�N�^�[[PassengerActor.h]
// �@�\�F�t�B�[���h����s��������A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PASSENGERACTOR_H_
#define _PASSENGERACTOR_H_

#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../Field/Place/PlaceConfig.h"

//**************************************
// �񋓎q�ݒ�
//**************************************
namespace FModel = Field::Model;

//**************************************
// �N���X��`
//**************************************
class PassengerActor :
	public GameObject
{
private:
	MeshContainer* mesh;

	// �萔��`
	static const D3DXVECTOR3 ActorScale;

public:
	PassengerActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	~PassengerActor();

	void Update();
	void Draw();

	void ChangeMesh(const char* nextTag);	// ���b�V���؂�ւ�
	void Move();							// �ړ�
};

#endif
