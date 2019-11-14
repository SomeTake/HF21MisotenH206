
//=============================================================================
//
// �����N���x���A�b�v�r���A�[���� [LinkLevelUpViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _LINK_LEVEL_UP_VIEWER_H_
#define _LINK_LEVEL_UP_VIEWER_H_

#include "../../Framework/BaseViewer.h"

#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;
class CountViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LinkLevelUpViewer :public BaseViewer
{
public:
	LinkLevelUpViewer();
	~LinkLevelUpViewer();

	void Update();
	void Draw(void);
	void Set(int level, std::function<void()> callback);

private:

	//�e�L�X�g
	BaseViewerDrawer *text;

	//���j��
	BaseViewerDrawer *laurel;

	//����
	CountViewerDrawer *num;

	//�{
	BaseViewerDrawer *plus;

	//�R�[���o�b�N
	std::function<void()> callback;

	//�r���A�[�Đ�
	void Play();

	//�t�F�[�h�C��
	void FadeIn();

	//�t�F�[�h�A�E�g
	void FadeOut();

	//�����o������
	void InNum();

	//�Đ������ǂ���
	bool isPlaying;

	//�t���[���J�E���g
	int countFrame;

	//���݂̃A�j���[�V����
	int currentAnim;

	//�p�����[�^���󂯎�锠
	int parameterBox;

	//�A�j���[�V��������
	float animTime;
};

#endif