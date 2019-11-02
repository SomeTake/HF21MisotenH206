//=====================================
//
// �C�x���g�A�N�^�[[EventActor.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#ifndef _EventActor_H_
#define _EventActor_H_

#include "../../Framework/Core/GameObject.h"
#include "../../Framework/Renderer3D/MeshContainer.h"


//**************************************
// �N���X��`
//**************************************
class EventActor : public GameObject
{
private:
	MeshContainer* mesh;								// ���b�V���R���e�i
	bool onCamera;

public:
	EventActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~EventActor();

	virtual void Update();
	virtual void Draw();

	void Rotate(float y);								// Y����]
	void SetPosition(const D3DXVECTOR3& Pos);			// ���W�Z�b�g
	void SetColor(const D3DXCOLOR& Color);				// ���b�V���̐F�ύX
	void ResetTransform();								// ���W�A��]�A�傫�������Z�b�g����
};

#endif
