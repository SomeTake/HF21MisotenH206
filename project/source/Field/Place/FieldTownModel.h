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
		//�R���X�g���N�^�A�f�X�g���N�^
		TownModel(const PlaceModel* place);
		~TownModel();

		//�o���ǉ�����
		void AddGate();

		//�o�Ă���l���̎擾����
		float DepatureNum();

		//�o�����擾����
		int GateNum();

		//�����N���x���擾����
		int LinkLevel();

		//���W�x�擾����
		float DevelopmentLevel();

		//���x�����オ��ۂɌĂ΂�鏈��
		void FindLinkedTown();

		//�����N���x�����Z����
		void AddLinkLevel(int num);

		//�v���C�X�擾����
		const PlaceModel* GetPlace();

	private:
		static const float BaseDepatureNum;		//��ƂȂ�o����

		//ID
		static unsigned incrementID;
		const int uniqueID;

		//�Q�Ƃ���v���C�X���f��
		const PlaceModel* place;

		//�o����
		int cntGate;

		//�����N���x��
		int linkLevel;

		//�����N���x���o�C�A�X
		int biasLinkLevel;

		//���W�x
		float developmentLevel;
	};
}
#endif