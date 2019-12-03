//=====================================
//
// �K�C�h�r���A�[�o�b�N�O���E���h[GuideViewerBG.h]
// �@�\�F�K�C�h�r���A�[�̔w�i
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GUIDEVIEWERBG_H_
#define _GUIDEVIEWERBG_H_

#include <vector>
using std::vector;

class PolygonDrawer;

//**************************************
// �N���X��`
//**************************************
class GuideViewerBG
{
private:
	int CountFrame;

	PolygonDrawer* background;
	vector<PolygonDrawer*> LeftWall;
	vector<PolygonDrawer*> RightWall;

public:
	GuideViewerBG();
	~GuideViewerBG();
	void Update(void);
	void Draw(void);
};

#endif
