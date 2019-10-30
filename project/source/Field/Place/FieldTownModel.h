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

#include <list>
#include <vector>
#include <functional>

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
		TownModel(const PlaceModel* place, std::function<void(std::vector<D3DXVECTOR3>&)> *action);
		~TownModel();

		//�X�V����
		void Update();

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
		
		//�o�H�ǉ�����
		void AddLinkedRoute(std::vector<D3DXVECTOR3>& route);

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

		//�t���[���J�E���^
		int cntFrame;

		//�p�b�Z���W���[�o������
		std::function<void(std::vector<D3DXVECTOR3>&)> *departPassenger;

		//�q�����Ă�X�ւ̌o�H
		std::list<std::vector<D3DXVECTOR3>> routeContainer;
	};
}
#endif