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
		PlaceContainer();
		~PlaceContainer();

		void Update();
		void Draw();

		PlaceModel* GetPlace(int x, int z);

		void LoadCSV(const char* filePath);

	private:
		const int PlaceRowMax = 100;			//1�s������̃v���C�X�ő吔
		const int PlaceColumMax = 100;			//1�񂠂���̃v���C�X�ő吔
		const int PlaceMax = 10000;				//�v���C�X�̍ő吔

		std::vector<PlaceModel*> placeVector;

		bool initialized;
	};
}

#endif