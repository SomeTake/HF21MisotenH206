//=====================================
//
// FieldControllerIdle.h
// �@�\:�t�B�[���h�R���g���[���A�C�h�����
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCONTROLLERIDLE_H_
#define _FIELDCONTROLLERIDLE_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../FieldController.h"

namespace Field
{
	/**************************************
	�N���X��`
	***************************************/
	class FieldController::IdleState : public BaseState<FieldController, FieldController::State>
	{
		void OnStart(FieldController &entity);
		State OnUpdate(FieldController& entity);
	};
}

#endif