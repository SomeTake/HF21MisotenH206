//=====================================
//
//PlaceConfig.h
//�@�\:�v���C�X�ݒ�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLACECONFIG_H_
#define _PLACECONFIG_H_

#include <vector>
#include <algorithm>
#include <memory>
#include "../../../Framework/Math/TMath.h"

/**************************************
�}�N����`
***************************************/
#define DEBUG_PLACEMODEL

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class RouteModel;
	class PlaceModel;

	/**************************************
	using�錾
	***************************************/
	using RouteModelPtr = std::shared_ptr<RouteModel>;
	using RouteContainer = std::vector<std::shared_ptr<RouteModel>>;

	/**************************************
	PlaceModel�̃^�C�v��\���񋓎q
	***************************************/
	enum PlaceType
	{
		None,			//�������
		Road,			//��
		Town,			//�X
		River,			//��
		Bridge,			//��
		Junction,		//�����_
		Mountain		//�R
	};

	/**************************************
	CSV�̃f�[�^��PlaceType�֕ϊ�����֐�
	***************************************/
	inline PlaceType IntToPlaceType(int n)
	{
		if (n == 0)
			return PlaceType::Town;

		if (n == 2)
			return PlaceType::River;

		if (n == 3)
			return PlaceType::Mountain;

		return PlaceType::None;
	}

	/**************************************
	�אڕ�����\���񋓎q
	***************************************/
	enum Adjacency
	{
		Back,			//Z�}�C�i�X�����̗א�
		Left,			//X�}�C�i�X�����̗א�
		Forward,		//Z�v���X�����̗א�
		Right,			//X�v���X�����̗א�
		Max,
		NotAdjacenct	//�אڂ��Ă��Ȃ�
	};

	/**************************************
	�אڕ����̋t�������߂鏈��
	***************************************/
	inline Adjacency GetInverseSide(const Adjacency adjacency)
	{
		if (adjacency >= Adjacency::Max)
			return NotAdjacenct;
		else
			return (Adjacency)Math::WrapAround(Adjacency::Back, Adjacency::Max, adjacency + 2);

	}

	// �ePlaceActor���Ƃ̃f�[�^���擾���邽�߂̍\����
	struct PlaceData
	{
		Field::FieldPosition key;
		int townLevel;
	};

}
#endif