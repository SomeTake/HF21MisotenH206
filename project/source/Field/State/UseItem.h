//=====================================
//
// UseItem.h
// �@�\:�A�C�e���g�p�X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _USEITEM_H_
#define _USEITEM_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../FieldController.h"

namespace Field
{
	/**************************************
	�N���X��`
	***************************************/
	class FieldController::UseItemState : public FieldController::ControllerState
	{
	public:
		void OnStart(FieldController& entity);
		State OnUpdate(FieldController& entity);
	};
}
#endif