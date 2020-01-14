//=====================================
//
//WorldBackGroundContainer.h
//�@�\:���[���h���x���̔w�i�R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WORLDBACKGROUNDCONTAINER_H_
#define _WORLDBACKGROUNDCONTAINER_H_

#include "../../../main.h"
#include "BackGroundContainer.h"

#include <vector>

/**************************************
�O���錾
***************************************/
class PlaceActor;
class InstancingMeshContainer;

namespace Field::Actor
{
	/**************************************
	�N���X��`
	***************************************/
	class WorldBackGroundContainer : public BackGroundContainer
	{
	public:
		WorldBackGroundContainer();
		~WorldBackGroundContainer();

		void Update();
		void Draw();

		void Load(int csvNo);

		bool IsSeaPlace(const FieldPosition& position) const;

		bool EnableAtlantis(const FieldPosition& position) const;

		void CreateAtlantis(const FieldPosition& position);

	private:
		InstancingMeshContainer *groundMesh;
		InstancingMeshContainer *seaMesh;

		std::vector<FieldPosition> seaMap;
	};
}
#endif