//=====================================
//
//FieldGround.h
//�@�\:�t�B�[���h�n��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDGROUND_H_
#define _FIELDGROUND_H_

#include "../../main.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldGround : public BoardPolygon, public GameObject
{
public:
	FieldGround();
	~FieldGround();

	void Draw();
};

#endif