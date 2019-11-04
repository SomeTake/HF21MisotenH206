//=====================================
//
// BaseBackGroundContainer.h
// �@�\:�w�i�A�N�^�[�R���e�i���N���X
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEBACKGROUNDCONTAINER_H_
#define _BASEBACKGROUNDCONTAINER_H_

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
	�N���X��`
	***************************************/
	class BackGroundContainer
	{
	public:
		BackGroundContainer();
		virtual ~BackGroundContainer();

		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual void Load() = 0;

	protected:
		std::vector<PlaceActor*> groundContainer;
		std::vector<PlaceActor*> riverContainer;
	};

}
#endif