//=============================================================================
//
// ���Viewer���� [BaseViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BASE_VIEWER_H_
#define _BASE_VIEWER_H_

//*****************************************************************************
// ���N���X��`
//*****************************************************************************
class BaseViewer
{
public:
	BaseViewer() {};
	virtual ~BaseViewer() {}

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
};

#endif

