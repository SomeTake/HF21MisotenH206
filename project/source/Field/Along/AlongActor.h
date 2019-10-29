//=====================================
//
//AlongActor.h
//�@�\:�������̃A�N�^�[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ALONGACTOR_H_
#define _ALONGACTOR_H_

#include "../../../main.h"

/**************************************
�O���錾
***************************************/
class MeshContainer;

namespace Field::Along
{
	/**************************************
	�N���X��`
	***************************************/
	class AlongActor : public GameObject
	{
	public:
		AlongActor();
		~AlongActor();

		void Update();
		void Draw(const D3DXMATRIX& parent);

		void PlayAnimation();

		void SetPosition(const D3DXVECTOR3& position) override;

	protected:
		static const float RangePositionOffset;
		static const float MinScale;
		static const float MaxScale;

		MeshContainer * mesh;
	};
}

#endif