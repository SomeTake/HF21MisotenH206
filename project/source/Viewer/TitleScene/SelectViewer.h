//=====================================
//
// �Z���N�g�r���A�[[SelectViewer.h]
// �@�\�F���[�h�Z���N�g�\���p
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _SELECTVIEWER_H_
#define _SELECTVIEWER_H_

#include "../../../main.h"
#include <vector>

class SubScreen;
class SelectCamera;
class SelectLogo;
//**************************************
// �N���X��`
//**************************************
class SelectViewer
{
public:
	// �I���ł��郂�[�h�̐�
	enum Mode {
		GameStart,
		TrophyCheck,
		Exit,
		Max
	};

	SelectViewer();
	~SelectViewer();
	void Update();
	void Draw();

	int CheckNextScene();
	// �Z���N�g���S�̕\����"�Q�[���J�n"�ɐݒ肷��
	void InitSelectLogo(void);

private:
	SubScreen* subScreen;
	SelectCamera* camera;
	std::vector<SelectLogo*> logo;
	int nextMode;

	static const D3DXVECTOR2 SubScreenSize;
	static const D3DXVECTOR2 SubScreenPos;
};

#endif