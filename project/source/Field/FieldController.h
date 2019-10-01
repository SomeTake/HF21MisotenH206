//=====================================
//
//FieldController.h
//�@�\:�t�B�[���h�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCONTROLLER_H_
#define _FIELDCONTROLLER_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class FieldCursor;
class FieldGround;

/**************************************
�N���X��`
***************************************/
class FieldController
{
public:
	FieldController();
	~FieldController();

	void Update();
	void Draw();

	void CheckInput();

private:
	const float PlaceOffset = 10.0f;		//Place��1�}�X���̃I�t�Z�b�g�l
	const float InitFieldBorder = 25;		//�t�B�[���h�͈͂̏����l

	FieldCursor *cursor;					//�J�[�\��
	FieldGround *ground;					//�n��

	int fieldBorder;						//�t�B�[���h�͈�(�}�X�P��)
};

#endif