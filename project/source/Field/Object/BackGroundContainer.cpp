//=====================================
//
//�w�i�A�N�^�[�R���e�i���N���X����[BaseBackGroundContainerh.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BackGroundContainer.h"
#include "../../FieldObject/Actor/PlaceActor.h"
#include "../../../Framework/Core/ObjectPool.h"

/**************************************
�R���X�g���N�^
***************************************/
Field::Actor::BackGroundContainer::BackGroundContainer()
{

}

/**************************************
�f�X�g���N�^
***************************************/
Field::Actor::BackGroundContainer::~BackGroundContainer()
{
	for (auto&& ground : groundContainer)
	{
		ObjectPool::Instance()->Destroy(ground);
	}
	groundContainer.clear();

	for (auto&& river : riverContainer)
	{
		ObjectPool::Instance()->Destroy(river);
	}
	riverContainer.clear();
}

/**************************************
�C����
***************************************/
bool Field::Actor::BackGroundContainer::IsSeaPlace(const FieldPosition& position) const
{
	return false;
}
