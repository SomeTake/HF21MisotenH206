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
class SkyBox;

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

		bool EnableAtlantis(const FieldPosition& position) const;

		static const char* SkyboxTexName[];

	private:
		InstancingMeshContainer *tearMesh;		//����̗􂯖ڂ̃��b�V��
		SkyBox *skybox;
	};
}
#endif