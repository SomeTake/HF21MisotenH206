//=====================================
//
// �A�N�^�[�A�j���[�V����[ActorAnimation.h]
// �@�\�F�A�N�^�[�ɊȒP�ȓ���������
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _ACTORANIMATION_H_
#define _ACTORANIMATION_H_

#include <functional>
#include "../../../Framework/Core/GameObject.h"
//**************************************
// �N���X��`
//**************************************
class ActorAnimation
{
	friend class Tween;
public:
	static void FallAndExpantion(GameObject& ref, std::function<void(void)> callback = nullptr);				// �������Ȃ���g��
	static void RotateAndExpantion(GameObject& ref, std::function<void(void)> callback = nullptr);	// ��]���Ȃ���g��
	static void RotateAndShrink(GameObject& ref, std::function<void(void)> callback = nullptr);		// ��]���Ȃ���k��
	static void Shrink(GameObject& ref, std::function<void(void)> callback = nullptr);				// �k��
	static void ExpantionYAndReturnToOrigin(GameObject& ref, std::function<void(void)> callback = nullptr);	// Y�����g�債�čŏI�I�ɂ��Ƃɖ߂�
};

#endif
