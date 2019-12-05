//=============================================================================
//
// �O���[�h�l�[���N���X [GradeNameViewer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _GradeNameViewer_H_
#define _GradeNameViewer_H_

#include "../../Framework/BaseViewer.h"
#include <functional>

class TextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class GradeNameViewer : public BaseViewer
{
private:
	TextureDrawer* GradeTitle;
	TextureDrawer* LineTex;
	std::function<void(void)> Callback;

public:
	GradeNameViewer();
	~GradeNameViewer();
	void Update(void);
	void Draw(void);
};

#endif
