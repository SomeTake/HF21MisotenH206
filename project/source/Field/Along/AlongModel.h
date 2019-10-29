//=====================================
//
//AlongModel.h
//�@�\:�������̌����̃��W�b�N���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ALONGMODEL_H_
#define _ALONGMODEL_H_

#include "../../../main.h"

#include <vector>

namespace Field::Along
{
	/**************************************
	�O���錾
	***************************************/
	class AlongActor;

	/**************************************
	�N���X��`
	***************************************/
	class AlongModel
	{
	public:
		//���^�C�v
		enum Type
		{
			Straight,
			T_Junction,
			Curve,
			CrossJunction,
			Max
		};

		//�R���X�g���N�^�A�f�X�g���N�^
		AlongModel(const Transform& transform);
		~AlongModel();

		//�X�V�����A�`�揈��
		void Update();
		void Draw();

		//���^�C�v�؂�ւ�����
		void SetType(Type type);

		//�A�N�^�[�쐬����
		void CreateActor();
	
	private:
		static const unsigned MaxActor[];							//�A�N�^�[�ő吔
		static const D3DXVECTOR3 StraightActorPosition[];			//�������̃A�N�^�[���W
		static const D3DXVECTOR3 T_JunctionActorPosition[];			//T���H�̃A�N�^�[���W
		static const D3DXVECTOR3 CurveActorPosition[];				//�J�[�u�̃A�N�^�[���W
		static const D3DXVECTOR3 CrossJunctionActorPosition[];		//�\���H�̃A�N�^�[���W

		std::vector<std::unique_ptr<AlongActor>> actorContainer;	//�A�N�^�[�R���e�i
		Transform *transform;										//���g��Transform
		Type type;													//���^�C�v

		D3DXVECTOR3 CalcActorPosition(int index);					//�A�N�^�[���W�v�Z����
	};
}

#endif