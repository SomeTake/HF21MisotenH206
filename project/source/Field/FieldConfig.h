//=====================================
//
//FieldConfig.h
//�@�\:�t�B�[���h�֘A�̐ݒ�l
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCONFIG_H_
#define _FIELDCONFIG_H_

#include "Place\PlaceConfig.h"

#include <vector>
#include <algorithm>

namespace Field
{
	/**************************************
	�f�[�^�ۑ��Ɏg�p����L�[
	***************************************/
	enum SaveKey
	{
		Key_FieldLevel,
		Key_Stock,
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
	PlaceModel�̍��W�\����
	***************************************/
	struct FieldPosition
	{
		int x, z;

		FieldPosition() : x(0), z(0) {}

		FieldPosition(int x, int z) : x(x), z(z) {}

		inline D3DXVECTOR3 ConvertToWorldPosition() const
		{
			return { x * 10.0f, 0.0f, z * -10.0f };
		}

		bool operator <(const FieldPosition& rhs) const
		{
			return std::tie(x, z) < std::tie(rhs.x, rhs.z);
		}

		FieldPosition operator + (const FieldPosition& rhs) const
		{
			return FieldPosition(x + rhs.x, z + rhs.z);
		}

	};

	/**************************************
	�t�B�[���h�̈ړ��\�ȋ��E
	***************************************/
	struct FieldBorder
	{
		int forward;		//Z�v���X�����̋��E
		int right;			//X�v���X�����̋��E
		int back;			//Z�}�C�i�X�����̋��E
		int left;			//Z�}�C�i�X�����̋��E

		FieldBorder(int forward, int right, int back, int left) :
			forward(forward), right(right), back(back), left(left)
		{

		}
	};

	/**************************************
	����������\���񋓎q
	***************************************/
	enum StraightType
	{
		NotStraight,
		BackAndForward,
		RightAndLeft
	};

	/**************************************
	���������̔��菈��
	***************************************/
	inline StraightType IsStraight(std::vector<Model::Adjacency>& adjacencyList)
	{
		if (adjacencyList.size() != 2)
			return StraightType::NotStraight;

		auto itrBack = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Back);
		auto itrForward = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Forward);
		if (itrBack != adjacencyList.end() && itrForward != adjacencyList.end())
			return StraightType::BackAndForward;

		auto itrRight = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Right);
		auto itrLeft = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Left);
		if (itrRight != adjacencyList.end() && itrLeft != adjacencyList.end())
			return StraightType::RightAndLeft;

		return StraightType::NotStraight;
	}

	/**************************************
	�J�[�u������\���񋓎q
	***************************************/
	enum CurveType
	{
		NotCurve,
		BackAndRight,
		BackAndLeft,
		LeftAndForward,
		ForwardAndRight
	};

	/**************************************
	�J�[�u�����̔��菈��
	***************************************/
	inline CurveType IsCurve(std::vector<Model::Adjacency>& adjacencyList)
	{
		assert(adjacencyList.size() == 2);

		auto itrBack = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Back);
		auto itrLeft = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Left);

		if (itrBack != adjacencyList.end() && itrLeft != adjacencyList.end())
			return CurveType::BackAndLeft;

		auto itrRight = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Right);
		if (itrBack != adjacencyList.end() && itrRight != adjacencyList.end())
			return CurveType::BackAndRight;

		auto itrForward = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Forward);
		if (itrLeft != adjacencyList.end() && itrForward != adjacencyList.end())
			return CurveType::LeftAndForward;
		else
			return CurveType::ForwardAndRight;

	}

	/**************************************
	�\���H�̌����񋓎q
	***************************************/
	enum TjunctionType
	{
		NotTjunction,
		ExceptBack,
		ExceptLeft,
		ExceptForward,
		ExceptRight
	};

	/**************************************
	�\���H�̌����̔��菈��
	***************************************/
	inline TjunctionType IsTjunction(std::vector<Model::Adjacency>& adjacencyList)
	{
		assert(adjacencyList.size() == 3);

		auto itr = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Back);
		if (itr == adjacencyList.end())
			return TjunctionType::ExceptBack;

		itr = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Left);
		if (itr == adjacencyList.end())
			return TjunctionType::ExceptLeft;

		itr = std::find(adjacencyList.begin(), adjacencyList.end(), Model::Adjacency::Forward);
		if (itr == adjacencyList.end())
			return TjunctionType::ExceptForward;

		return TjunctionType::ExceptRight;
	}
}

#endif