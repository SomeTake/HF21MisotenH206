//=============================================================================
//
// ���ʃr���A�[�R���g���[������ [ResultViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_VIEWER_H_
#define _RESULT_VIEWER_H_

#include <vector>
#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class ResultScoreViewer;
class ResultAchieveViewer;
class ResultViewerParam;
class BaseViewer;
class GuideActor;
class SubScreen;
class Camera;

namespace RewardConfig
{
	enum Type : int;
}

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class ResultViewer
{
public:
	enum ResultAnimation
	{
		PlayingIn,
		Idle,
		PlayingOut
	};

	ResultViewer();
	~ResultViewer();

	void Update(void);
	void Draw(void);

	//�A�N�e�B�u��Ԃ��Z�b�g
	void SetActive(bool flag);

	//�p�����[�^�̎󂯎�菈��
	void ReceiveParam(int cityScore,int worldScore,int spaceScore);

	//�X�R�A�r���[�A�̃A�j���[�V�����Đ�������
	ResultAnimation IsPlayingAnimation() const;

	//���уr���[���Z�b�g
	void SetAchiveViewer(std::vector<RewardConfig::Type>& rewardContainer, std::function<void()> callback = nullptr);

	//�X�R�A�r���[�����X���C�h�C��������
	void SlideScoreViewer(bool isIn);

private:
	std::vector <BaseViewer*> resultViewer;
	ResultScoreViewer * scoreViewer;
	ResultAchieveViewer *achieveViewer;
	ResultViewerParam *viewerParam;

	bool isActive;

	//��ʉE�ɕ\�����郍�{
	GuideActor* actor;

	//���{��`�悷�郌���_�����O�^�[�Q�b�g
	SubScreen* screen;

	//���{�`��p�̃J����
	Camera *camera;
};

#endif

