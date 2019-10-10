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

namespace Field::Model
{
	/**************************************
	�^�G�C���A�X
	***************************************/
	class RouteModel;
	class PlaceModel;

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
	�t�B�[���h���x���̃^�C�v��\���񋓎q
	***************************************/
	enum FieldLevel
	{
		City,	// �s�s���x��
		World,	// �����x��
		Space,	// �����x��
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
	Adjacency�񋓎q�̌�u�C���N�������g
	***************************************/
	inline Adjacency operator++(Adjacency& adjacency, int)
	{
		return (adjacency == Adjacency::Max) ? adjacency : Adjacency(adjacency + 1);
	}

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
}
#endif