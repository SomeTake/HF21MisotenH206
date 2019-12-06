//=====================================
//
// �K�C�h�r���A�[[GuideViewer.h]
// �@�\�F�K�C�h���L�����N�^�[�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GUIDEVIEWER_H_
#define _GUIDEVIEWER_H_

#include "../../../../Framework/Pattern/BaseSingleton.h"
#include "../../../../Framework/PostEffect/Effect/CRTFilter.h"
#include <string>
#include "GuideActor.h"
#include <deque>
#include "../../../../Framework/Sound/SoundEffect.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class GuideCamera;
class GuideViewerBG;
class GuideCallOutViewer;
class SubScreen;

//**************************************
// �N���X��`
//**************************************
struct GuideViewerData
{
	std::string message;
	GuideActor::AnimState animation;
	SE::VoiceType voice;
	GuideViewerData(std::string message, GuideActor::AnimState next, SE::VoiceType voice) {
		this->message = message;
		this->animation = next;
		this->voice = voice;
	}
};

//**************************************
// �N���X��`
//**************************************
class GuideViewer :
	public BaseSingleton<GuideViewer>
{
	friend class BaseSingleton<GuideViewer>;
public:
	void Init();	// �e��C���X�^���X�̏�����
	void Uninit();	// �e��C���X�^���X�̍폜

	void Update();
	void Draw();

	void SetActive(bool flag);

	// ���b�Z�[�W���Z�b�g
	void SetMessage(const std::string &message);
	// �A�j���[�V������ύX
	void ChangeAnim(GuideActor::AnimState next);

	// ��̂Q��VOICE�̍Đ����܂Ƃ߂čs��
	void SetData(const std::string& message, GuideActor::AnimState next, SE::VoiceType voice);

private:
	// �e��C���X�^���X�p�|�C���^
	GuideActor* actor;
	GuideCamera* camera;
	GuideViewerBG* bg;
	CRTFilter* filter;
	GuideCallOutViewer *callOutViewer;
	SubScreen* subScreen;

	std::deque<GuideViewerData*> que;	// �A�j���[�V�����A���b�Z�[�W�ASE�����ԂɎ��[����L���[
	SE::VoiceType prev;
	int cntQue;
	bool isActive;	// �`��۔���

	static const D3DXVECTOR2 SubScreenPosition;
	static const D3DXVECTOR2 SubScreenSize;

	GuideViewer() {}
	~GuideViewer() {}

	void UpdateDeque();

};

#endif
