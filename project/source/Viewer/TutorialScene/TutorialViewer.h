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

	void Init(void);
	void Update();
	void Draw();
	// �`���[�g���A���̐�����ʂ�\��
	void ShowTutorial(HelpTextureType Type);
	// �w���v�e�L�X�g��\��
	void SetHelpMessage(void);
	void SetIsShowTexture(bool Flag) { this->IsShowTexture = Flag; };
	bool GetIsShowTexture(void) { return this->IsShowTexture; };
	void SetActive(bool Flag) { this->isPlaying = Flag; };

private:
	TextureDrawer *BackGround;
	TextureDrawer *MessageFrame;
	std::vector<TextureDrawer*> HelpTexture;
	TextViewer *DescriptionText;
	TextViewer *ExitText;
	int TextureNum;
	bool IsShowTexture;
};

#endif