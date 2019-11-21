
//=============================================================================
//
// �A�ŃQ�[�����ʃr���A�[���� [BeatResultViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BEAT_RESULT_VIEWER_H_
#define _BEAT_RESULT_VIEWER_H_

#include "../../Framework/BaseViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class BeatResultViewer :public BaseViewer
{
public:
	BeatResultViewer();
	~BeatResultViewer();

	//���ʂ̎��
	enum ResultID
	{
		Success,
		Failed,
		Max
	};

	void Update();
	void Draw(void);
	void Set(ResultID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer * text;
	BaseViewerDrawer *bg;

	//�Đ��I���ʒm
	std::function<void(void)> Callback;

	//�Đ�
	void Play();

	//�e�N�X�`�����󂯓n��
	void SetTexture(ResultID id);

	//�w�i���I�[�v��
	void OpenBG(void);

	//�w�i���N���[�Y
	void CloseBG(void);

	//�Đ������ǂ���
	bool isPlaying;

	//�t���[���J�E���g
	int countFrame;

	//���݂̃A�j���[�V����
	int currentAnim;

	//�A�j���[�V��������
	float animTime;
};

#endif