//=====================================
//
// �Q�[���T�u[GameSub.h]
// �@�\�F�T�u�E�C���h�E
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GAMESUB_H_
#define _GAMESUB_H_

#include "../../main.h"
#include "../../Framework/Core/BaseGame.h"

//**************************************
// �N���X��`
//**************************************
class GameSub :
	public BaseGame
{
	GameSub(HINSTANCE hInstance, HWND hWnd);

	void Update()override;
};

#endif

