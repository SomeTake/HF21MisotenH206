//=====================================
//
// �Z���N�g���S[SelectLogo.h]
// �@�\�F�Z���N�g���S
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _SELECTLOGO_H_
#define _SELECTLOGO_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"

//**************************************
// �N���X��`
//**************************************
class SelectLogo :
	BillboardObject
{
private:
	BoardPolygon* polygon;

public:
	SelectLogo();
	~SelectLogo();

	void Update();
	void Draw();

	void LoadResource(const char* tag);
	void SetPosition(const D3DXVECTOR3& pos);
	void SetTexDiv(const D3DXVECTOR2& div);
	void SetTextureIndex(int index);
};

#endif
