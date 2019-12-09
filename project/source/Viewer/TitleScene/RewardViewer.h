//=============================================================================
//
// �����[�h�r���[�A�N���X [RewardViewer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _RewardViewer_H_
#define _RewardViewer_H_

#include "../../Viewer/Framework/BaseViewer.h"
#include <vector>
using std::vector;

class TextureDrawer;
class TextViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RewardViewer : public BaseViewer
{
private:
	vector<TextureDrawer*> TextureVec;
	TextureDrawer* Title;
	TextureDrawer* RewardIcon;
	TextureDrawer* RewardFrame;
	TextureDrawer* RewardName;
	TextureDrawer* Cursor;
	TextViewer* Text;

	void CursorMove(void);

public:
	RewardViewer();
	~RewardViewer();
	void Update(void);
	void Draw(void);
};

#endif
