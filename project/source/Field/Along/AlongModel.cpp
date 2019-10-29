//=====================================
//
//AlongModel.cpp
//�@�\:�������̌����̃��W�b�N���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "AlongModel.h"

namespace Field::Along
{
	/**************************************
	static�����o
	***************************************/
	//�A�N�^�[�ő吔
	const unsigned AlongModel::MaxActor[Type::Max] = {
		10, 7, 10, 4
	};

	//�������̃A�N�^�[���W
	const D3DXVECTOR3 AlongModel::StraightActorPosition[] = {
		{-4.0f, 0.0f, -2.0f},
		{ 4.0f, 0.0f, -4.0f},
		{-4.0f, 0.0f, 0.0f},
		{ 4.0f, 0.0f, 2.0f },
		{-4.0f, 0.0f, 2.0f},
		{ 4.0f, 0.0f, -2.0f},
		{ -4.0f, 0.0f, 2.0f },
		{ 4.0f, 0.0f, 0.0f},
		{-4.0f, 0.0f, -4.0f},
		{ 4.0f, 0.0f, 2.0f}
	};

	//T���H�̃A�N�^�[���W
	const D3DXVECTOR3 AlongModel::T_JunctionActorPosition[] = {
		{ -4.0f, 0.0f, 4.0f },
		{ 2.0f, 0.0f, 4.0f },
		{ -2.0f, 0.0f, 4.0f },
		{ 4.0f, 0.0f, 4.0f },
		{ -4.0f, 0.0f, -4.0f },
		{ 4.0f, 0.0f, -4.0f },
		{ 0.0f, 0.0f, 4.0f },
	};
	
	//�J�[�u�̃A�N�^�[���W
	const D3DXVECTOR3 AlongModel::CurveActorPosition[] = {
		{ 2.0f, 0.0f, -4.0f },
		{ -4.0f, 0.0f, -4.0f },
		{ 4.0f, 0.0f, 0.0f },
		{ -2.0f, 0.0f, -4.0f },
		{ 4.0f, 0.0f, -2.0f },
		{ 4.0f, 0.0f, 4.0f },
		{ 0.0f, 0.0f, -4.0f },
		{ 4.0f, 0.0f, -4.0f },
		{ -4.0f, 0.0f, 4.0f },
		{ 4.0f, 0.0f, 2.0f },
	};

	//�\���H�̃A�N�^�[���W
	const D3DXVECTOR3 AlongModel::CurveActorPosition[] = {
		{ -4.0f, 0.0f, -4.0f },
		{ -4.0f, 0.0f, 4.0f },
		{ 4.0f, 0.0f, -4.0f },
		{ 4.0f, 0.0f, 4.0f },
	};

	/**************************************
	�R���X�g���N�^
	***************************************/
	AlongModel::AlongModel(const Transform& transform)
	{
		actorContainer.reserve(10);

		this->transform = new Transform(transform);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	AlongModel::~AlongModel()
	{
		actorContainer.clear();
		SAFE_DELETE(transform);
	}

	/**************************************
	�X�V����
	***************************************/
	void AlongModel::Update()
	{
		//�A�N�^�[�̍X�V����
		for (auto&& actor : actorContainer)
		{
			
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void AlongModel::Draw()
	{
		D3DXMATRIX mtxWorld = transform->GetMatrix();

		//���g��Transform�𔽉f�����ăA�N�^�[��`��
		for (auto&& actor : actorContainer)
		{

		}
	}

	/**************************************
	�^�C�v�Z�b�g����
	***************************************/
	void AlongModel::SetType(Type type)
	{
		this->type = type;
		
		//�A�N�^�[�̐��𒲐�
		if (actorContainer.size() >= MaxActor[type])
		{
			actorContainer.resize(MaxActor[type]);
		}

		//�ʒu�𒲐�
		for (auto&& actor : actorContainer)
		{

		}
	}

	/**************************************
	�A�N�^�[�쐬����
	***************************************/
	void AlongModel::CreateActor()
	{
		//�A�N�^�[���ő吔�ɓ��B���Ă����瑁�����^�[��
		if (actorContainer.size() >= MaxActor[type])
			return;

		D3DXVECTOR3 position = CalcActorPosition(actorContainer.size());

		//�A�N�^�[�𐶐����Ēǉ�
	}

	/**************************************
	�A�N�^�[���W�v�Z����
	***************************************/
	D3DXVECTOR3 AlongModel::CalcActorPosition(int index)
	{
		if (type == Straight)
			return StraightActorPosition[index];

		if (type == T_Junction)
			return T_JunctionActorPosition[index];

		if (type == Curve)
			return CurveActorPosition[index];

		if (type == CrossJunction)
			return CrossJunctionActorPosition[index];
	}

}