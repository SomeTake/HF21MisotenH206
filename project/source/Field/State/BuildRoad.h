//=====================================
//
// BuildRoad.h
// �@�\:�����r���h����X�e�[�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BuildRoad_H_
#define _BuildRoad_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../FieldController.h"

namespace Field
{
	/**************************************
	�O���錾
	***************************************/

	/**************************************
	�N���X��`
	***************************************/
	class FieldController::BuildRoadState : public BaseState<FieldController, FieldController::State>
	{
	public:
		void OnStart(FieldController& entity);
		State OnUpdate(FieldController& entity);
	};
}
#endif