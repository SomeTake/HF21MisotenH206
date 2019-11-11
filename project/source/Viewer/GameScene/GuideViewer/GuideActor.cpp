#include "GuideActor.h"

const GuideActor::AnimData GuideActor::data[] = {
	{"Idle", 1.0f, 0.1f, 0.1f},
};

GuideActor::GuideActor()
{
	transform->SetPosition(D3DXVECTOR3(150.0f, 0.0f, -150.0f));
	transform->SetScale(Vector3::One);
	transform->SetRotation(Vector3::Zero);
	SetActive(true);

	// �A�j���[�V�����̍쐬
	anim = new AnimationManager();
	//anim->LoadXFile();

	// �A�j���[�V�����Z�b�g�̍쐬
	for (int i = 0; i < AnimMax; i++)
	{
		anim->LoadAnimation(data[i].tag, AnimState(i), data[i].shiftTime);
		anim->SetPlaySpeed(i, data[i].playSpeed);
		anim->SetDeltaTime(i, data[i].deltaTime);
	}

	// �A�j���[�V�����J�ڂ̃Z�b�g
	//anim->SetFinishTransition();
}

GuideActor::~GuideActor()
{
	SAFE_DELETE(anim);
}

void GuideActor::Update()
{
	anim->Update();
}

void GuideActor::Draw()
{
	if (!IsActive())
		return;

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	transform->SetWorld();

	anim->Draw(&mtxWorld);
}

void GuideActor::ChangeAnim(AnimState next)
{
	anim->ChangeAnim((UINT)next, true);
}