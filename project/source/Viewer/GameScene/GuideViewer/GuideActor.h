//=====================================
//
// �K�C�h�A�N�^�[[GuideViewer.h]
// �@�\�F�K�C�h���L�����N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _GUIDEACTOR_H_
#define _GUIDEACTOR_H_

#include "../../../../Framework/Core/GameObject.h"
#include "../../../../Framework/Animation/AnimationManager.h"

//**************************************
// �N���X��`
//**************************************
class GuideActor :
	public GameObject
{
public:
	// �A�j���[�V�����X�e�[�g
	enum AnimState
	{
		Idle,
		Cheering,	// �E�����グ�ĐU��
		Clapping,	// ����
		Excited,	// ����킿��킿��炫��낫���
		FistPump,	// �E��ŃO�b�ƃK�b�c�|�[�Y
		Pain,		// ���ɒɂ݂�
		Waving,		// ���A�ǂ����ǂ���
		Yeah,		// ����ŃO�b�ƃK�b�c�|�[�Y
		ShakeFist,	// �E����グ�ĐU��
		Salute,		// �h��
		WaveHand,	// ��̑O�Ŏ���ӂ�i���₢��Ȃ��Ȃ��A�݂����ȁj
		Defeat,		// �����ŕ����Ă����[���Ċ���
		Surprised,	// �����[�I�H
		TalkingTypeA,	// ������L���ăA�s�[�����Ȃ���b��
		TalkingTypeB,	// �d�b���Ă銴��
		SecretTalk,		// �����b

		// �ő吔
		AnimMax
	};

	// �A�j���[�V�����ǂݍ��݃f�[�^�p�\����
	struct AnimData
	{
		const char* tag;
		float playSpeed;
		float shiftTime;
		float deltaTime;
	};

	GuideActor();
	~GuideActor();

	void Update();
	void Draw();

	void ChangeAnim(AnimState next);

private:
	AnimationManager* anim;					// �A�j���[�V�����}�l�[�W��
	static const AnimData data[AnimMax];	// �A�j���[�V�����ǂݍ��ݗp�f�[�^
	static const char* FileName;			// �ǂݍ���X�t�@�C��

	void Debug();
};

#endif

