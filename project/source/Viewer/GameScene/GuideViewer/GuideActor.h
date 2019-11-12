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
		Running,
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
};

#endif

