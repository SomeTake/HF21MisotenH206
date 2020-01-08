//=====================================
//
//�x�[�X�G�~�b�^����[BaseEmitter.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseEmitter.h"
#include "BaseParticle.h"
#include "ParticleRenderer.h"

#include "../Camera/Camera.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BaseEmitter::BaseEmitter() :
	GameObject(false),
	emitNum(1),
	duration(1),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseEmitter::BaseEmitter(int emitNum) :
	GameObject(false),
	emitNum(emitNum),
	duration(2),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseEmitter::BaseEmitter(int emitNum, int duration) :
	GameObject(false),
	emitNum(emitNum),
	duration(duration),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(duration == 0)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseEmitter::BaseEmitter(int emitNum, int durationMin, int durationMax) :
	GameObject(false),
	emitNum(emitNum),
	duration(Math::RandomRange(durationMin, durationMax)),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseEmitter::BaseEmitter(int emitNumMin, int emitNumMax, int durationMin, int durationMax) :
	GameObject(false),
	emitNum(Math::RandomRange(emitNumMin, emitNumMax)),
	duration(Math::RandomRange(durationMin, durationMax)),
	useCull(false),
	isFinished(true),
	enableEmit(false),
	flgLoop(false)
{

}

/**************************************
�f�X�g���N�^
***************************************/
BaseEmitter::~BaseEmitter()
{
	Utility::DeleteContainer(particleContainer);
}

/**************************************
����������
***************************************/
void BaseEmitter::Init(const std::function<void(void)>& callback)
{
	cntFrame = 0;
	active = true;
	isFinished = false;
	enableEmit = true;

	this->callback = callback;

	for (auto&& particle : particleContainer)
	{
		particle->SetActive(false);
	}
}

/**************************************
�X�V����
***************************************/
void BaseEmitter::Update()
{
	if (!active)
		return;

	cntFrame++;
	Emit();

	//�p�[�e�B�N���̍X�V
	isFinished = true;
	for (auto&& particle : particleContainer)
	{
		if (!particle->IsActive())
			continue;

		isFinished = false;

		particle->Update();
	}

	//�I���m�F
	if (cntFrame >= duration && !flgLoop)
	{
		enableEmit = false;

		if (isFinished)
		{
			active = false;

			if(callback != nullptr)
				callback();
		}
	}
}

/**************************************
���o����
***************************************/
bool BaseEmitter::Emit()
{
	if (!enableEmit)
		return true;

	D3DXVECTOR3 screenPos = Camera::MainCamera()->Projection(transform->GetPosition());

	if (useCull)
	{
		if (screenPos.x < 0.0f || screenPos.x > SCREEN_WIDTH || screenPos.y < 0.0f || screenPos.y > SCREEN_HEIGHT)
			return true;
	}

	UINT cntEmit = 0;
	for (auto& particle : particleContainer)
	{
		if (particle->IsActive())
			continue;

		//����������
		particle->SetTransform(*transform);
		particle->Init();

		//�J�E���g
		cntEmit++;

		//���߂�ꐔ�������o���Ă�����I��
		if (cntEmit == emitNum)
			return true;
	}

	return false;
}

/**************************************
�A�N�e�B�u����
***************************************/
//bool BaseEmitter::IsActive() const
//{
//	if (!active)
//		return false;
//
//	if (duration == 0)
//		return true;
//
//	return isFinished;
//}

/**************************************
�J�����O�g�p�ݒ�
***************************************/
void BaseEmitter::UseCulling(bool value)
{
	useCull = value;
}

/**************************************
�`������p�[�e�B�N�������_���[�ɂ킽��
***************************************/
void BaseEmitter::PushRenderParameter(std::shared_ptr<ParticleRenderer> renderer)
{
	if (!active)
		return;

	for (auto&& particle : particleContainer)
	{
		if (!particle->IsActive())
			continue;

		D3DXMATRIX mtxWorld = particle->GetWorldMtx();
		ParticleUV uv = particle->GetUV();

		renderer->PushParticleParameter(mtxWorld, uv);
	}
}

/**************************************
�p�[�e�B�N�����o�̒�~
***************************************/
void BaseEmitter::Stop()
{
	enableEmit = false;
}

/**************************************
���[�v�ݒ�
***************************************/
void BaseEmitter::Loop(bool state)
{
	flgLoop = state;
}
