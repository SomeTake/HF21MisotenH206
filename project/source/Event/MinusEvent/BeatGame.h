//*****************************************************************************
// 11/15(��)�`�����͂܉���
//*****************************************************************************

//=============================================================================
//
// �A�ŃQ�[���C�x���g�N���X [BeatGame.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _BeatGame_H_
#define _BeatGame_H_

#include "../../Viewer/GameScene/BeatGameViewer/BeatTitleViewer.h"
#include "../EventBase.h"
#include <functional>
#include <string>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BeatGameViewer;
class BeatTitleViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatGame : public EventBase
{
private:
	int countInput;
	float countFrame;
	bool TelopOver;
	bool isSuccess;
	bool isReady;
	bool isFinished;
	bool canSetReady;
	bool canSetGo;
	std::function<void(bool)> Callback;

	void EventOver(void);

	//�������������菈��
	bool IsSuccess(void);

	//���s���������菈��
	bool IsFailed(void);

	//���f�B�[�e�L�X�g�Z�b�g����
	void SetReadyText(void);

	//�S�[�e�L�X�g�Z�b�g����
	void SetGoText(void);

	//�A�ŃQ�[���r���A�[
	BeatGameViewer *beatGameViewer;

	//�Q�[���^�C�g���擾
	BeatTitleViewer::TitleID GetGameTitle(void);

public:

	enum GameType
	{
		AILevelDecrease,
		BanStockUse,
		CityDestroyEvent,
	};

	//�Đ����̃C�x���g
	GameType playingEvent;

	BeatGame(BeatGame::GameType type,std::function<void(bool)> CallBack = nullptr);
	~BeatGame();
	void Update(void) override;
	void Draw(void) override;
	string GetEventMessage(int FieldLevel) override;
	void CountdownStart(void);
};

#endif
