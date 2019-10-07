//=====================================
//
// �A�C�e���A�N�^�[[ItemActor.h]
// �@�\�F�A�C�e���̃A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _ITEMACTOR_H_
#define _ITEMACTOR_H_

#include "../../../Framework/Renderer3D/BoardPolygon.h"

//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class ReverseItemActor;
class ItemActor :
	public BoardPolygon
{
private:
	Transform* transform;
	ReverseItemActor* reverse;				// �����p

	// �萔��`
	static const D3DXVECTOR2 ActorSize;		// �T�C�Y
	static const float RotValue;			// ��]���x

public:
	ItemActor(const D3DXVECTOR3& pos);
	~ItemActor();

	void Update();
	void Draw();
	void Rotate(float y);
};

//**************************************
// �����p�N���X��`
//**************************************
class ReverseItemActor :
	public BoardPolygon
{
private:
	Transform* transform;

public:
	ReverseItemActor(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR2& size);
	~ReverseItemActor();
	void Update();
	void Draw();
	void Rotate(float y);
};

#endif
