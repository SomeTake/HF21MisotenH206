//=====================================
//
// �K�C�h�r���A�[�o�b�N�O���E���h[GuideViewerBG.h]
// �@�\�F�K�C�h�r���A�[�̔w�i
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GUIDEVIEWERBG_H_
#define _GUIDEVIEWERBG_H_

#include "../../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../../Framework/Core/GameObject.h"

//**************************************
// �N���X��`
//**************************************
class GuideViewerBG :
	public GameObject
{
private:
	BoardPolygon* polygon;
public:
	GuideViewerBG();
	~GuideViewerBG();

	void Update();
	void Draw();
};

#endif
