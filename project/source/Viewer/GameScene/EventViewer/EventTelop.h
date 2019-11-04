
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
#include <vector>
#include <functional>

//�e���b�v�̎��
enum TelopID
{
	PositiveEvent01,
	PositiveEvent02,
	NegativeEvent01,
	NegativeEvent02
};

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

	//�e���b�v�̎�ސ�
	static const int typeMax = 4;

	void Update();
	void Draw(void);
	void Set(TelopID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer *text;
	BaseViewerDrawer *bg;

	//�Đ��I���ʒm
	std::function<void(void)> Callback;

	//�e�L�X�g�̃e�N�X�`�����R���e�i
	std::vector <LPDIRECT3DTEXTURE9> textTexContainer;

	//�w�i�̃e�N�X�`�����R���e�i
	std::vector <LPDIRECT3DTEXTURE9> bgTexContainer;

	//�Đ�
	void Play();

	//�e�N�X�`�����󂯓n��
	void PassTexture(TelopID id);

	//�w�i���I�[�v��
	void OpenBG(void);

	//�w�i���N���[�Y
	void CloseBG(void);

	//�w�i�̃A�N�e�B�u�p�[�Z���e�[�W
	float percentageBG;

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