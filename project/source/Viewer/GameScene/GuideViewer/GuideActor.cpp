#include "GuideActor.h"
#include "../../../../Framework/Tool/DebugWindow.h"

const GuideActor::AnimData GuideActor::data[] = {
	{"Idle", 1.0f, 0.1f, 1 / 30.0f},
	{"Running", 1.0f, 0.1f, 1 / 30.0f}
};

GuideActor::GuideActor()
{
	transform->SetPosition(D3DXVECTOR3(150.0f, 0.0f, -150.0f));
	transform->SetScale(Vector3::One);
	transform->SetRotation(Vector3::Zero);
	SetActive(true);

	// �A�j���[�V�����̍쐬
	anim = new AnimationManager();
	anim->LoadXFile("data/MODEL/Boy.x", "Guide");

	// �A�j���[�V�����Z�b�g�̍쐬
	for (int i = 0; i < AnimMax; i++)
	{
		anim->LoadAnimation(data[AnimState(i)].tag, i, data[AnimState(i)].shiftTime);
		anim->SetPlaySpeed(i, data[AnimState(i)].playSpeed);
		anim->SetDeltaTime(i, data[AnimState(i)].deltaTime);
	}

	// �A�j���[�V�����J�ڂ̃Z�b�g
	anim->SetFinishTransition(Running, Idle);
	anim->SetFinishTransition(Idle, Idle);
}

GuideActor::~GuideActor()
{
	//anim�̃f�X�g���N�^�͕s�v
}

void GuideActor::Update()
{
	anim->Update();

	Debug::Begin("GuideActor");

	if (Debug::Button("ChangeAnim:Running"))
	{
		anim->ChangeAnim(Running);
	}

	Debug::End();
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