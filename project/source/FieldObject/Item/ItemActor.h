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
// �O���錾
//**************************************
class BoardPolygon;

//**************************************
// �N���X��`
//**************************************
class ItemActor :
	public GameObject
{
private:
	// �萔��`
	static const D3DXVECTOR2 ActorSize;		// �T�C�Y
	static const float RotValue;			// ��]���x

	BoardPolygon *polygon;

public:
	ItemActor(const D3DXVECTOR3& pos);
	~ItemActor();

	//�|���S���p�̃��\�[�X�쐬�Ȃǂ̏���������
	static void Init();

	void Update();
	void Draw();
	void Rotate(float y);
};
#endif
