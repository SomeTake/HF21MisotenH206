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
#include <unordered_map>

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class PlaceModel;
	class TownModel;

	/**************************************
	�N���X��`
	***************************************/
	class JunctionModel
	{
	public:
		using TownContainer = std::unordered_map<unsigned, TownModel*>;

		//�R���X�g���N�^�A�f�X�g���N�^
		JunctionModel(const PlaceModel* place);
		~JunctionModel();

		//���G�x�v�Z����
		void Calculate(TownContainer& townContainer);

		//���G�x�擾����
		float TrafficJam(TownContainer& townContainer);

	private:
		//ID
		static unsigned incrementID;
		const unsigned uniqueID;

		//�Q�Ƃ���v���C�X���f��
		const PlaceModel* place;

		//���G�x
		float trafficJam;
	};
}
#endif