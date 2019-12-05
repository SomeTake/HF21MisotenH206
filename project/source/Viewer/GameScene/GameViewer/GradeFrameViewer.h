//=============================================================================
//
// �O���[�h�t���[���N���X [GradeFrameViewer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _GradeFrameViewer_H_
#define _GradeFrameViewer_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

class TextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class GradeFrameViewer : public BaseViewer
{
private:
	TextureDrawer* FrameUp;
	TextureDrawer* FrameDown;
	std::function<void(void)> Callback;


public:
	GradeFrameViewer();
	~GradeFrameViewer();
	void Update(void);
	void Draw(void);
	void SlideIn(std::function<void(void)> callback = nullptr);
	void SlideOut(std::function<void(void)> callback = nullptr);
};

#endif
