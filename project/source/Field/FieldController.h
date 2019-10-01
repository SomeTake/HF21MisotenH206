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
	FieldCursor *cursor;
	FieldGround *ground;

};

#endif