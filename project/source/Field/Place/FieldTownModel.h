//=====================================
//
//FieldTownModel.h
//�@�\:�X�̃��W�b�N���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDTOWNMODEL_H_
#define _FIELDTOWNMODEL_H_

#include "../../../main.h"

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class PlaceModel;

	/**************************************
	�N���X��`
	***************************************/
	class TownModel
	{
	public:
		TownModel(PlaceModel* place);
		~TownModel();

		void AddGate();

		float DepatureNum();

		int GateNum();

	private:
		static const float BaseDepatureNum;

		static unsigned incrementID;
		const int uniqueID;

		const PlaceModel* place;

		int cntGate;
	};
}
#endif