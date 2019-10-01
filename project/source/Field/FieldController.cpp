//=====================================
//
//FieldController.cpp
//�@�\:�t�B�[���h�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldController.h"
#include "FieldCursor.h"
#include "FieldGround.h"

#include "../../Framework/Input/input.h"

/**************************************
�R���X�g���N�^
***************************************/
FieldController::FieldController()
{
	//�C���X�^���X�쐬
	cursor = new FieldCursor();
	ground = new FieldGround();
}

/**************************************
�f�X�g���N�^
***************************************/
FieldController::~FieldController()
{
	SAFE_DELETE(cursor);
	SAFE_DELETE(ground);
}

/**************************************
�X�V����
***************************************/
void FieldController::Update()
{
	cursor->Update();
}

/**************************************
�`�揈��
***************************************/
void FieldController::Draw()
{
	ground->Draw();

	//�J�[�\���ɂ͓��߃I�u�W�F�N�g���܂܂��̂ōŌ�ɕ`��
	cursor->Draw();
}

/**************************************
���͊m�F����
***************************************/
void FieldController::CheckInput()
{

}
