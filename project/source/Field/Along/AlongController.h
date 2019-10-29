//=====================================
//
//AlongController.h
//�@�\:�������̏��R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ALONGCONTROLLER_H_
#define _ALONGCONTROLLER_H_

#include "../../../main.h"

#include <map>

namespace Field::Along
{
	/**************************************
	�O���錾
	***************************************/
	class AlongModel;

	/**************************************
	AlongPosition�\����
	***************************************/
	struct AlongPosition
	{
		AlongPosition(const D3DXVECTOR3& position);
		bool operator<(const AlongPosition& rhs) const;

		float x, z;
	};

	/**************************************
	�N���X��`
	***************************************/
	class AlongController
	{
	public:
		enum RoadType
		{
			Straight,
			T_Junction,
			Curve,
			CrossJunction,
		};

		AlongController();
		~AlongController();

		void Update();
		void Draw();

		void OnReachPassenger(const D3DXVECTOR3& position);
		void OnBuildRoad(const Transform& transform, RoadType type);

	private:
		using AlongModelMap = std::map<AlongPosition, std::unique_ptr<Along::AlongModel>>;

		AlongModelMap modelMap;
	};
}


#endif