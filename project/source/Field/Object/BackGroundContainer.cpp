//=====================================
//
//�w�i�A�N�^�[�R���e�i���N���X����[BaseBackGroundContainerh.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BackGroundContainer.h"
#include "../../FieldObject/Actor/PlaceActor.h"

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
	Utility::DeleteContainer(groundContainer);
	Utility::DeleteContainer(riverContainer);
}

/**************************************
�C����
***************************************/
bool Field::Actor::BackGroundContainer::IsSeaPlace(const FieldPosition& position) const
{
	return false;
}
