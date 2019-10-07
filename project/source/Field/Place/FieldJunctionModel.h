//=====================================
//
//FieldJunctionModel.h
//�@�\:�����_�̃��W�b�N���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDJUNCTIONMODEL_H_
#define _FIELDJUNCTIONMODEL_H_

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
	class JunctionModel
	{
	public:
		JunctionModel(const PlaceModel* place);
		~JunctionModel();

		float TrafficJam();

	private:
		static unsigned incrementID;
		const unsigned uniqueID;

		const PlaceModel* place;
	};
}
#endif