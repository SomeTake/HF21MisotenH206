//=====================================
//
// �K�C�h�A�N�^�[[GuideViewer.h]
// �@�\�F�K�C�h���L�����N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GuideActor.h"
#include "../../../../Framework/Tool/DebugWindow.h"

//=====================================
// �X�^�e�B�b�N�����o������
//=====================================
const GuideActor::AnimData GuideActor::data[] = {
	{"Idle", 1.0f, 0.3f, 1 / 30.0f},
	{"Cheering", 1.0f, 0.3f, 1 / 30.0f},
	{"Clapping", 1.0f, 0.3f, 1 / 30.0f}, 
	{"Excited", 1.0f, 0.3f, 1 / 30.0f}, 
	{"FistPump", 1.0f, 0.3f, 1 / 30.0f},
	{"Pain", 1.0f, 0.3f, 1 / 30.0f},
	{"Waving", 1.0f, 0.3f, 1 / 30.0f},
	{"Yeah", 1.0f, 0.3f, 1 / 30.0f},
	{"ShakeFist", 1.0f, 0.3f, 1 / 30.0f},
	{"Salute", 1.0f, 0.3f, 1 / 30.0f},
	{"WaveHand", 1.0f, 0.3f, 1 / 30.0f},
	{"Defeat", 1.0f, 0.3f, 1 / 30.0f},
	{"Surprised", 1.0f, 0.3f, 1 / 30.0f},
	{"TalkingTypeA", 1.0f, 0.3f, 1 / 30.0f},
	{"TalkingTypeB", 1.0f, 0.3f, 1 / 30.0f},
	{"SecretTalk", 1.0f, 0.3f, 1 / 30.0f},
};

const char* GuideActor::FileName = "data/MODEL/Robot.X";

//=====================================
// �R���X�g���N�^
//=====================================
GuideActor::GuideActor()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 15.0f));
	transform->SetScale(Vector3::One * 0.3f);
	transform->SetRotation(Vector3::Zero);
	SetActive(true);

	// �A�j���[�V�����̍쐬
	anim = new AnimationManager();
	anim->LoadXFile(FileName, "Guide");

	// �A�j���[�V�����Z�b�g�̍쐬
	for (int i = 0; i < AnimMax; i++)
	{
		anim->LoadAnimation(data[AnimState(i)].tag, i, data[AnimState(i)].shiftTime);
		anim->SetPlaySpeed(i, data[AnimState(i)].playSpeed);
		anim->SetDeltaTime(i, data[AnimState(i)].deltaTime);
	}

	// �A�j���[�V�����J�ڂ̃Z�b�g
	for (int i = 0; i < AnimMax; i++)
	{
		// �Ƃ肠�����S���A�j���[�V�����I��������A�C�h���ɖ߂�
		anim->SetFinishTransition(AnimState(i), AnimState(0));
	}
}

//=====================================
// �f�X�g���N�^
//=====================================
GuideActor::~GuideActor()
{
	//anim�̃f�X�g���N�^�͕s�v
	SAFE_DELETE(anim);
}

//=====================================
// �X�V
//=====================================
void GuideActor::Update()
{
	anim->Update();

	Debug();
}

//=====================================
// �`��
//=====================================
void GuideActor::Draw()
{
	if (!IsActive())
		return;

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	transform->SetWorld();

	anim->Draw(&mtxWorld);
}

//=====================================
// �w��̈ʒu�Ɍ�������
//=====================================
void GuideActor::LookAt(const D3DXVECTOR3 & pos)
{
	transform->LookAt(pos);
	transform->Rotate(180.0f, transform->Up());
}

//=====================================
// �A�j���[�V�����؂�ւ�
//=====================================
void GuideActor::ChangeAnim(AnimState next)
{
	anim->ChangeAnim((UINT)next, true);
}

//=====================================
// �f�o�b�O
//=====================================
void GuideActor::Debug()
{
	Debug::Begin("GuideActorAnimation");

	if (Debug::Button("Cheering"))
	{
		anim->ChangeAnim(Cheering);
	}
	if (Debug::Button("Clapping"))
	{
		anim->ChangeAnim(Clapping);
	}
	if (Debug::Button("Excited"))
	{
		anim->ChangeAnim(Excited);
	}
	if (Debug::Button("FistPump"))
	{
		anim->ChangeAnim(FistPump);
	}
	if (Debug::Button("Pain"))
	{
		anim->ChangeAnim(Pain);
	}
	if (Debug::Button("Waving"))
	{
		anim->ChangeAnim(Waving);
	}
	if (Debug::Button("Yeah"))
	{
		anim->ChangeAnim(Yeah);
	}
	if (Debug::Button("ShakeFist"))
	{
		anim->ChangeAnim(ShakeFist);
	}
	if (Debug::Button("Salute"))
	{
		anim->ChangeAnim(Salute);
	}
	if (Debug::Button("WaveHand"))
	{
		anim->ChangeAnim(WaveHand);
	}
	if (Debug::Button("Defeat"))
	{
		anim->ChangeAnim(Defeat);
	}
	if (Debug::Button("Surprised"))
	{
		anim->ChangeAnim(Surprised);
	}
	if (Debug::Button("TalkingTypeA"))
	{
		anim->ChangeAnim(TalkingTypeA);
	}
	if (Debug::Button("TalkingTypeB"))
	{
		anim->ChangeAnim(TalkingTypeB);
	}
	if (Debug::Button("SecretTalk"))
	{
		anim->ChangeAnim(SecretTalk);
	}

	Debug::End();

}