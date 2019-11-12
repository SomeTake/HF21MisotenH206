//=====================================
//
//�t�B�[���h�R���g���[���A�C�h����ԏ���[FieldControllerIdle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "FieldControllerIdle.h"
#include "../Controller/FieldInput.h"
#include "../Object/FieldCursor.h"
#include "../../Viewer/GameScene/FieldViewer/OperationExplanationViewer.h"
#include "../Place/FieldPlaceModel.h"

namespace Field
{
	/**************************************
	���ꏈ��
	***************************************/
	void FieldController::IdleState::OnStart(FieldController & entity)
	{
		//���ɉ������Ȃ�
	}

	/**************************************
	�X�V����
	***************************************/
	FieldController::State FieldController::IdleState::OnUpdate(FieldController & entity)
	{
		State next = State::Idle;

		//����������X�V
		entity.operationZ = entity.GetPlace()->CanStartRoute() ?
			OperationExplanationViewer::OperationID::Z_Build :
			OperationExplanationViewer::OperationID::Z_None;

		entity.operationX = entity.enableDevelop ?
			OperationExplanationViewer::OperationID::X_Develop :
			OperationExplanationViewer::OperationID::X_None;

		entity.operationSpace = OperationExplanationViewer::OperationID::Space_Change;

		//Z�L�[�������ꂽ��Build�֑J��
		if (entity.input->GetBuildTrigger())
		{
			entity.cursor->SetMode(FieldCursor::Mode::BuildRoad);
			next = State::Build;
		}

		//X�L�[�������ꂽ��Develop�֑J��
		if (entity.input->GetDevelopTrigger() && entity.enableDevelop)
		{
			entity.cursor->SetMode(FieldCursor::Mode::Develop);
			next = State::Develop;
		}

		return next;
	}

}