//=====================================
//
//�A�C�e���g�p����[UseItem.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "UseItem.h"

namespace Field
{
	/**************************************
	���ꏈ��
	***************************************/
	void FieldController::UseItemState::OnStart(FieldController & entity)
	{

	}

	/**************************************
	�X�V����
	***************************************/
	FieldController::State FieldController::UseItemState::OnUpdate(FieldController & entity)
	{
		return State::UseItem;
	}
}