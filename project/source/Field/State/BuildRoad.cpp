//=====================================
//
//�e���v���[�g����[BuildRoad.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BuildRoad.h"
#include "../../../Framework/Input/input.h"
#include "../Place/OperatePlaceContainer.h"

namespace Field
{
	/**************************************
	���ꏈ��
	***************************************/
	void FieldController::BuildRoadState::OnStart(FieldController & entity)
	{
		
	}

	/**************************************
	���ꏈ��
	***************************************/
	FieldController::State FieldController::BuildRoadState::OnUpdate(FieldController & entity)
	{
		return State::BuildRoad;
	}

}