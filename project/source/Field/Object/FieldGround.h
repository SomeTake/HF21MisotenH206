//=====================================
//
//FieldGround.h
//�@�\:�t�B�[���h�n��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDGROUND_H_
#define _FIELDGROUND_H_

#include "../../../main.h"

class BoardPolygon;

namespace Field
{
	/**************************************
	�O���錾	
	***************************************/

	/**************************************
	�N���X��`
	***************************************/
	class FieldGround : public GameObject
	{
	public:
		FieldGround();
		~FieldGround();

		void Draw();

	private:
		BoardPolygon * polygon;
	};
}
#endif