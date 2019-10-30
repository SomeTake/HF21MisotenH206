//=============================================================================
//
// �A�ŃQ�[���r���[�A�N���X [BeatGameViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _BeatGameViewer_H_
#define _BeatGameViewer_H_

#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatGameViewer 
{
private:
	int CountFrame;
	float ExpandPercent;
	bool DrawFlag;
	std::function<void(void)> Callback;

	BaseViewerDrawer* Viewer;
	LPDIRECT3DTEXTURE9 SuccessTexture;
	LPDIRECT3DTEXTURE9 FailTexture;

	void SetVertex();
	void TextureExpand();

public:
	BeatGameViewer();
	~BeatGameViewer();
	void Update(void);
	void Draw(void);
	void DrawStart(bool IsSuccess,std::function<void(void)> Callback);
};

#endif

