//=====================================
//
// �A�N�^�[�A�j���[�V����[ActorAnimation.cpp]
// �@�\�F�A�N�^�[�ɊȒP�ȓ���������
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "ActorAnimation.h"
#include "../../../Framework/Tween/Tween.h"
#include "../Actor/PlaceActor.h"

//=====================================
// �������Ȃ���g��
//=====================================
void ActorAnimation::FallAndExpantion(GameObject& ref, std::function<void(void)> callback)
{
	const int duration = 15;
	Tween::Move(ref, ref.GetPosition() + D3DXVECTOR3(0.0f, 10.0f, 0.0f), ref.GetPosition(), duration, InQuint);
	Tween::Scale(ref, D3DXVECTOR3(0.0f, 0.0f, 0.0f), Vector3::One * 0.25f, duration, OutCubic, callback);
}

//=====================================
// ��]���Ȃ���g��
//=====================================
void ActorAnimation::RotateAndExpantion(GameObject& ref, std::function<void(void)> callback)
{
	const int duration = 30;
	Tween::Rotate(ref, ref.GetRotation() + D3DXVECTOR3(0.0f, 180.0f, 0.0f), ref.GetRotation(), duration, OutBack);
	Tween::Scale(ref, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ref.GetScale(), duration, OutBack, callback);
}

//=====================================
// ��]���Ȃ���k��
//=====================================
void ActorAnimation::RotateAndShrink(GameObject& ref, std::function<void(void)> callback)
{
	Tween::Rotate(ref, ref.GetRotation() + D3DXVECTOR3(0.0f, 180.0f, 0.0f), ref.GetRotation(), 30, OutCirc);
	Tween::Scale(ref, ref.GetScale(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30, OutCirc, callback);
}

//=====================================
// �k��
//=====================================
void ActorAnimation::Shrink(GameObject& ref, std::function<void(void)> callback)
{
	Tween::Scale(ref, ref.GetScale(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30, OutCirc, callback);
}

//=====================================
// Y�����g�債�čŏI�I�ɂ��Ƃɖ߂�
//=====================================
void ActorAnimation::ExpantionYAndReturnToOrigin(GameObject& ref, std::function<void(void)> callback) 
{
	Tween::Scale(ref, ref.GetScale(), ref.GetScale() + D3DXVECTOR3(0.0f, 0.1f, 0.0f), 30, OutBack, [&ref, &callback] 
	{
		Tween::Scale(ref, ref.GetScale(), ref.GetScale() - D3DXVECTOR3(0.0f, 0.1f, 0.0f), 30, InOutQuint, [&callback]
		{
			callback;
		});
	});
}