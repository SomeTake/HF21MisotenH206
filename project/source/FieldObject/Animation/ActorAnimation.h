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
	static void Fall(GameObject& ref, std::function<void(void)> callback = nullptr);
	static void RotateAndExpantion(GameObject& ref, std::function<void(void)> callback = nullptr);
	static void RotateAndShrink(GameObject& ref, std::function<void(void)> callback = nullptr);

};

#endif
