//=====================================
//
// �^�C�g�����S[TitleLogo.h]
// �@�\�F�^�C�g�����S�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "../../../Framework/Renderer2D/Polygon2D.h"
//**************************************
// �N���X��`
//**************************************
class TitleLogo :
	public Polygon2D
{
private:
	static const D3DXVECTOR3 InitPos;
	static const D3DXVECTOR2 InitSize;

public:
	TitleLogo();
	~TitleLogo();

	void Update();
	void Draw();

};

#endif

