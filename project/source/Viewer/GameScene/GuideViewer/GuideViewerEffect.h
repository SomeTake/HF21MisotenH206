//=====================================
//
// �K�C�h�r���A�[�G�t�F�N�g[GuideViewerEffect.h]
// �@�\�F�K�C�h�r���A�[�̃G�t�F�N�g
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GUIDEVIEWEREFFECT_H_
#define _GUIDEVIEWEREFFECT_H_

#include "../../../../Framework/Core/GameObject.h"
#include "../../../../Framework/Renderer2D/Polygon2D.h"

//**************************************
// �N���X��`
//**************************************
class GuideViewerEffect :
	public GameObject
{
private:
	Polygon2D* polygon;

public:
	GuideViewerEffect();
	~GuideViewerEffect();

	void Update();
	void Draw();
};

#endif

