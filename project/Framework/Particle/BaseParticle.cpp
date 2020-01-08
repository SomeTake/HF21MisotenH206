//=====================================
//
//�x�[�X�p�[�e�B�N������[BaseParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseParticle.h"

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
BaseParticle::BaseParticle() :
	uv(ParticleUV()),
	lifeFrame(1), maxLife(1), minLife(1)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseParticle::BaseParticle(int life) :
	uv(ParticleUV()),
	lifeFrame(life), minLife(life), maxLife(1)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseParticle::BaseParticle(int lifeMin, int lifeMax) :
	uv(ParticleUV()),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax)),
	minLife(lifeMin), maxLife(lifeMax)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseParticle::BaseParticle(float u, float v, int lifeMin, int lifeMax) :
	uv(ParticleUV(u, v)),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax)),
	minLife(lifeMin), maxLife(lifeMax)
{
}

/**************************************
�R���X�g���N�^
***************************************/
BaseParticle::BaseParticle(const BaseParticle & rhs) :
	uv(rhs.uv),
	lifeFrame(Math::RandomRange(rhs.maxLife, rhs.minLife)),
	minLife(rhs.minLife), maxLife(rhs.maxLife)
{
}

/**************************************
�f�X�g���N�^
***************************************/
BaseParticle::~BaseParticle()
{
}

/**************************************
UV���W�擾
***************************************/
ParticleUV BaseParticle::GetUV() const
{
	return uv;
}

/**************************************
�A�N�e�B�u����
***************************************/
bool BaseParticle::_IsActive() const
{
	return cntFrame <= lifeFrame;
}
