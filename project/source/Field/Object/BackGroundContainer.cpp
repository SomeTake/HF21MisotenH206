//=====================================
//
//�w�i�A�N�^�[�R���e�i���N���X����[BaseBackGroundContainerh.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BackGroundContainer.h"

/**************************************
�R���X�g���N�^
***************************************/
Field::Actor::BackGroundContainer::BackGroundContainer()
{
	groundContainer.reserve(2000);
	riverContainer.reserve(500);
}

/**************************************
�f�X�g���N�^
***************************************/
Field::Actor::BackGroundContainer::~BackGroundContainer()
{
	Utility::DeleteContainer(groundContainer);
	Utility::DeleteContainer(riverContainer);
}
