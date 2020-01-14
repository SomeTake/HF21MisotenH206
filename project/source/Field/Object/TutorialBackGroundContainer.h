//=============================================================================
//
// �`���[�g���A���p�n�ʃR���e�i�N���X [TutorialBackGroundContainer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _TutorialBackGroundContainer_H_
#define _TutorialBackGroundContainer_H_

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
	class TutorialBackGroundContainer : public BackGroundContainer
	{
	public:
		TutorialBackGroundContainer();
		~TutorialBackGroundContainer();

		void Update();
		void Draw();

		void Load(int csvNo);

		bool EnableAtlantis(const FieldPosition& position) const;

	private:
		InstancingMeshContainer *groundMesh;
	};
}
#endif