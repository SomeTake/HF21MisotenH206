//=====================================
//
//PlaceContainer.h
//�@�\:�v���C�X�R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLACECONTAINER_H_
#define _PLACECONTAINER_H_

#include "../../../main.h"
#include <vector>

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class PlaceModel;

	/**************************************
	�N���X��`
	***************************************/
	class PlaceContainer
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		PlaceContainer();
		~PlaceContainer();

		//�X�V�����A�`�揈��
		void Update();
		void Draw();

		//�w�肵���}�X�ڂ�PlaceModel���擾
		PlaceModel* GetPlace(int x, int z);

		//CSV�f�[�^�ǂݍ���
		void LoadCSV(const char* filePath);

	private:
		const int PlaceMax = 10000;				//�v���C�X�̍ő吔

		std::vector<PlaceModel*> placeVector;	//PlaceModel�R���e�i

		int placeRowMax;						//1�s������̃v���C�X�ő吔
		int placeColumMax;						//1�񂠂���̃v���C�X�ő吔

		bool initialized;						//�������t���O

		void MakeAdjacency();
	};
}

#endif