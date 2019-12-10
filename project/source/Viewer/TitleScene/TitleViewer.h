//=====================================
//
// �^�C�g���r���A�[[TitleViewer.h]
// �@�\�F�^�C�g�����UI�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _TITLEVIEWER_H_
#define _TITLEVIEWER_H_

#include "../../../main.h"

class TitleLogo;
class SelectViewer;
class GameScene;
class RewardViewer;

//**************************************
// �N���X��`
//**************************************
class TitleViewer
{
private:
	TitleLogo* logo;
	SelectViewer* selectViewer;
	RewardViewer* rewardViewer;

	bool isActive;

public:
	TitleViewer();
	~TitleViewer();

	void Update();
	void Draw();

	void SetActive(bool flag);

	bool CheckSceneChange();
	void SetNextScene(GameScene& entity);
	// �Z���N�g���S�̕\����"�Q�[���J�n"�ɐݒ肷��
	void InitSelectLogo(void);
};

#endif
