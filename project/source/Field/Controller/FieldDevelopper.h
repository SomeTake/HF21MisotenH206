//=====================================
//
//FieldDevelopper.h
//�@�\:�t�B�[���h�J���@�\
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDDEVELOPPER_H_
#define _FIELDDEVELOPPER_H_

#include "../../../main.h"
#include "../FieldController.h"

/**************************************
�O���錾
***************************************/

namespace Field
{ 
	/**************************************
	�N���X��`
	***************************************/
	class FieldController::FieldDevelopper
	{
	public:
		FieldDevelopper(FieldController* controller);
		~FieldDevelopper();

		void BuildRoad();

		void DevelopPlace(PlaceVector& route, PlaceIterator start);
		PlaceIterator DevelopMountain(PlaceVector& route, PlaceIterator mountain);
		PlaceIterator DevelopRiver(PlaceVector& route, PlaceIterator river);

	private:
		FieldController *entity;
	};
}

#endif