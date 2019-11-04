//=====================================
//
// BackGroundActorContainer.h
// �@�\:�w�i�A�N�^�[�̃R���e�i
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BACKGROUNDACTORCONTAINER_H_
#define _BACKGROUNDACTORCONTAINER_H_

#include "../../../main.h"
#include <vector>

#include "../FieldConfig.h"

/**************************************
�O���錾
***************************************/
class PlaceActor;

namespace Field::Actor
{
	/**************************************
	�O���錾
	***************************************/

	/**************************************
	�N���X��`	
	***************************************/
	class BackGroundActorContainer
	{
	public:
		BackGroundActorContainer(FieldLevel level);
		~BackGroundActorContainer();

		void Update();
		void Draw();

		void Load();

	private:
		FieldLevel fieldLevel;
		std::vector<PlaceActor*> groundContainer;
		std::vector<PlaceActor*> riverContainer;
	};
}
#endif