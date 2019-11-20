//=====================================
//
// CityBackGroundContainer.h
// �@�\:�w�i�A�N�^�[�̃R���e�i
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CITYBACKGROUNDCONTAINER_H_
#define _CITYBACKGROUNDCONTAINER_H_

#include "../../../main.h"
#include "BackGroundContainer.h"

#include <vector>
#include <map>

#include "../FieldConfig.h"

/**************************************
�O���錾
***************************************/
class PlaceActor;
class InstancingMeshContainer;

namespace Field::Actor
{
	/**************************************
	�O���錾
	***************************************/

	/**************************************
	�N���X��`	
	***************************************/
	class CityBackGroundContainer : public BackGroundContainer
	{
	public:
		CityBackGroundContainer();
		~CityBackGroundContainer();

		void Update();
		void Draw();

		void Load();

		bool EnableAtlantis(const FieldPosition& position) const;

	private:
		InstancingMeshContainer *groundMesh;

		std::map<FieldPosition, int> LoadRiverFlowData();
	};
}
#endif