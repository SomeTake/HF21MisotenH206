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
class PlaceModel;

/**************************************
�N���X��`
***************************************/
class FieldController
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	FieldController();
	~FieldController();

	//�X�V�A�`�揈��
	void Update();
	void Draw();

	//���͊m�F����
	void CheckInput();

private:
	const float PlaceOffset = 10.0f;		//Place��1�}�X���̃I�t�Z�b�g�l
	const float InitFieldBorder = 25;		//�t�B�[���h�͈͂̏����l

	FieldCursor *cursor;					//�J�[�\��
	FieldGround *ground;					//�n��
	PlaceModel *model;						//3D���f���}�l�[�W��

	int fieldBorder;						//�t�B�[���h�͈�(�}�X�P��)
};

#endif