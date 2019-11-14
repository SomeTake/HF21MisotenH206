
//=============================================================================
//
// �C�x���g�e���b�v���� [EventTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_TELOP_H_
#define _EVENT_TELOP_H_

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
class EventTelop :public BaseViewer
{
public:
	EventTelop();
	~EventTelop();

	//�e���b�v�̎��
	enum TelopID
	{
		//�V���M�������e�B���B�I�I
		Singularity,
		//�A�g�����e�B�X�o��I�I
		Atlantis,
		//�V�f���𔭌��I�I
		NewPlanet,
		//覐΂��ڋߒ��I�I
		Meteorite,
		//�F���l���P���I�I
		Alien,
		//AI�X�g���C�L�����I�I
		AI_Strike,
		//��ސ�
		Max
	};

	void Update();
	void Draw(void);
	void Set(TelopID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer *text;
	BaseViewerDrawer *bg;

	//�Đ��I���ʒm
	std::function<void(void)> Callback;

	//�Đ�
	void Play();

	//�e�N�X�`�����󂯓n��
	void PassTexture(TelopID id);

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