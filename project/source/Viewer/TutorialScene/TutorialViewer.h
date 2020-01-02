//=============================================================================
//
// �`���[�g���A���r���[�A�N���X [TutorialViewer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _TutorialViewer_H_
#define _TutorialViewer_H_

#include "../../../main.h"
#include "../Framework/BaseViewer.h"

#include <functional>
#include <vector>

/**************************************
�O���錾
***************************************/
class TextureDrawer;
class TextViewer;

/**************************************
�N���X��`
***************************************/
class TutorialViewer : public BaseViewer
{
public:
	enum HelpTextureType
	{
		LinkRoad,
		Develop,
		ChangeCamera,
		EventHappend,
		HighScore,
		Max,
	};

	TutorialViewer();
	~TutorialViewer();

	void Update();
	void Draw();
	void ShowTutorial(HelpTextureType Type);

private:
	TextureDrawer *BackGround;
	TextureDrawer *MessageFrame;
	std::vector<TextureDrawer*> HelpTexture;
	TextViewer *DescriptionText;
	TextViewer *TitleText;
	int TextureNum;
};

#endif