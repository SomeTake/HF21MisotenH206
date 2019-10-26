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
class GameViewerParam;

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

		void AddStock(int num);

		void EmbedViewerParam(GameViewerParam& param);

		static const int MaxStock;
		static const int InitStock;

	private:
		FieldController *entity;

		int stockNum;
	};
}

#endif