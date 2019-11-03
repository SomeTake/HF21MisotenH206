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
	D3DXVECTOR3 BaseHoverPos;
	MeshContainer* mesh;							// ���b�V���R���e�i
	int FrameCount;
	bool InHoverMotion;

	void HoverMotion(void);							// �z�o�����O�^��
public:
	EventActor(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag);
	~EventActor();

	virtual void Update();
	virtual void Draw();

	void Rotate(float y);							// Y����]
	void SetPosition(const D3DXVECTOR3& Pos);		// ���W�Z�b�g
	void SetHoverMotion(bool Flag);
};	

#endif
