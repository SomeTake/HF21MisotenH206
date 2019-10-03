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
#include "../FieldObject/PlaceModel.h"

#include "../../Framework/Input/input.h"

namespace Field
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder)
	{
		//�C���X�^���X�쐬
		cursor = new FieldCursor();
		ground = new FieldGround();

		model = new ::PlaceModel();

		//�J�[�\���̈ړ��͈͂�������
		cursor->SetBorder(fieldBorder * PlaceOffset, fieldBorder * PlaceOffset);
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
		model->Update();

	}

	/**************************************
	�`�揈��
	***************************************/
	void FieldController::Draw()
	{
		ground->Draw();

		model->Draw();

		//�J�[�\���ɂ͓��߃I�u�W�F�N�g���܂܂��̂ōŌ�ɕ`��
		cursor->Draw();
	}

	/**************************************
	���͊m�F����
	***************************************/
	void FieldController::CheckInput()
	{
		float x = 0.0f, z = 0.0f;

		//X�������̓��͂�X���ړ��Ƃ��Ď擾
		x = Input::GetRepeatHorizontal();

		//X�������͂�����������Y�����͂��m�F�i�΂߈ړ����֎~���邽�߁j
		if (x == 0.0f)
		{
			z = Input::GetRepeatVertical();
		}

		//�J�[�\�����ړ�
		cursor->Move(D3DXVECTOR3(x, 0.0f, z) * PlaceOffset);
	}

	/**************************************
	�J�[�\���擾����
	***************************************/
	GameObject * FieldController::GetFieldCursor()
	{
		return cursor;
	}
}