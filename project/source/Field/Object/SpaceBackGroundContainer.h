//=====================================
//
//SpaceBackGroundContainer.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPACEBACKGROUNDCONTAINER_H_
#define _SPACEBACKGROUNDCONTAINER_H_

#include "../.././GameMain.h"
#include "BackGroundContainer.h"

/**************************************
�O���錾
***************************************/
class InstancingMeshContainer;

namespace Field::Actor
{
	/**************************************
	�N���X��`
	***************************************/
	class SpaceBackGroundContainer : public BackGroundContainer
	{
	public:
		SpaceBackGroundContainer();
		~SpaceBackGroundContainer();

		void Update();
		void Draw();

		void Load();

		bool IsSeaPlace(const FieldPosition& position) const;

	private:
		InstancingMeshContainer * tearMesh;		//����̗􂯖ڂ̃��b�V��
	};
}
#endif