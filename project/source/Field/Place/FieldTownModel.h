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
#include "../FieldConfig.h"

#include <list>
#include <vector>
#include <functional>
#include <utility>

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
		TownModel(const PlaceModel* place, std::function<void(const PlaceModel *start, const PlaceModel *goal)> *action);
		~TownModel();

		//�X�V����
		void Update();

		//�o���ǉ�����
		void AddGate(const PlaceModel* gate);

		//�o�Ă���l���̎擾����
		float DepatureNum();

		//�o�����擾����
		int GateNum();

		//�����N���x���擾����
		int LinkLevel();

		//���W�x�擾����
		float DevelopmentLevel();

		//�q�����Ă���X��T������
		void FindLinkedTown();

		//�����N���x�����Z����
		void AddLinkLevel(int num);

		//�v���C�X�擾����
		const PlaceModel* GetPlace();
		
		//�o�H�ǉ�����
		void AddLinkedTown(const PlaceModel *place);

	private:
		static const float BaseDepatureNum;		//��ƂȂ�o����

		//ID
		static unsigned incrementID;
		const int uniqueID;

		//�Q�Ƃ���v���C�X���f��
		const PlaceModel* place;

		//�����N���x��
		int linkLevel;

		//�����N���x���o�C�A�X
		int biasLinkLevel;

		//���W�x
		float developmentLevel;

		//�t���[���J�E���^
		int cntFrame;

		//�ǂ̊X�֌����킹�邩
		int indexDestination;

		//�p�b�Z���W���[�o������
		std::function<void(const PlaceModel* start, const PlaceModel *end)> *departPassenger;

		//�q�����Ă�X�ւ̌o�H
		//first : ����̊X, second : �o��
		std::vector<std::pair<const PlaceModel*, const PlaceModel*>> linkedTown;

		//�o��
		std::vector<const PlaceModel*> gateList;

		//�T�����̏o���̃C���f�b�N�X
		unsigned indexSearchingGate;
	};
}
#endif