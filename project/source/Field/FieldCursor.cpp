//=====================================
//
//FieldCursor.cpp
//�@�\:�t�B�[���h�J�[�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCursor.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Tool/DebugWindow.h"

#include <algorithm>

namespace Field
{
	/**************************************
	static�ϐ�
	***************************************/
	const D3DXVECTOR2 FieldCursorSquare::Size = { 5.0f, 5.0f };
	const int FieldCursorSquare::FadeDuration = 30;
	const float FieldCursorSquare::MoveSpeed = 0.3f;

	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldCursor::FieldCursor(float positionOffset) :
		PositionOffset(positionOffset),
		borderX(0), borderZ(0),
		position(0, 0),
		cntMove(MoveDuration)
	{
		//�l�p�`����
		squareContainer.resize(SquareMax);
		for (auto&& square : squareContainer)
		{
			square = new FieldCursorSquare();
		}
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	FieldCursor::~FieldCursor()
	{
		Utility::DeleteContainer(squareContainer);
	}

	/**************************************
	�X�V����
	***************************************/
	void FieldCursor::Update()
	{
		//�ړ�
		Move();

		//30�t���[�������Ɏl�p�`�𔭐�
		if (cntFrame == 0)
		{
			SetSquare();
		}
		cntFrame = Math::WrapAround(0, EmitInterval, ++cntFrame);

		//�l�p�`�X�V
		for (auto&& square : squareContainer)
		{
			square->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void FieldCursor::Draw()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//���g�̃��[���h�ϊ��s����쐬
		D3DXMATRIX mtxWorld = transform->GetMatrix();

		//�l�p�`���\�[�g���ĕ`��
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		std::sort(squareContainer.begin(), squareContainer.end(), &FieldCursorSquare::Compare);

		for (auto&& square : squareContainer)
		{
			square->Draw(mtxWorld);
		}

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	/**************************************
	�ړ�����
	***************************************/
	void FieldCursor::Move(int x, int z)
	{
		if (x == 0 && z == 0)
			return;

		if (cntMove <= MoveDuration)
			return;

		//�ړ��J�n�n�_��ۑ�
		startPos = CalcWorldPosition();

		//X���̈ړ���D�悵�Ďg�p(Clamp�ňړ��͈͂𐧌�)
		if (x != 0)
			position.x = Math::Clamp(0, borderX - 1, position.x + x);
		else
			position.z = Math::Clamp(0, borderZ - 1, position.z + z);

		//�ړ�����W���v�Z
		moveTarget = CalcWorldPosition();

		//�J�E���g���Z�b�g
		cntMove = 0;
	}

	/**************************************
	���W�ݒ�
	***************************************/
	void FieldCursor::SetModelPosition(int x, int z)
	{
		position.x = x;
		position.z = z;
	}

	/**************************************
	�ړ��͈͐ݒ菈��
	***************************************/
	void FieldCursor::SetBorder(int borderX, int borderZ)
	{
		this->borderX = borderX;
		this->borderZ = borderZ;
	}

	/**************************************
	���W�擾����
	***************************************/
	Model::PlacePosition FieldCursor::GetModelPosition() const
	{
		return position;
	}

	/**************************************
	FieldCursorSquare�Z�b�g����
	***************************************/
	void FieldCursor::SetSquare()
	{
		auto itr = std::find_if(squareContainer.begin(), squareContainer.end(), [](auto&& square)
		{
			return !square->IsActive();
		});

		if (itr != squareContainer.end())
		{
			(*itr)->Set();
		}
	}

	/**************************************
	FieldCursor�ړ�����
	***************************************/
	void FieldCursor::Move()
	{
		cntMove++;

		if (cntMove > MoveDuration)
			return;

		float t = 1.0f * cntMove / MoveDuration;
		D3DXVECTOR3 position = Easing::EaseValue(t, startPos, moveTarget, EaseType::Linear);
		transform->SetPosition(position);
	}

	/**************************************
	���[���h���W�n�_����
	***************************************/
	D3DXVECTOR3 FieldCursor::CalcWorldPosition() const
	{
		return D3DXVECTOR3((position.x) * PositionOffset, 0.0f, (position.z) * PositionOffset);
	}

	/**************************************
	FieldCursorSquare�R���X�g���N�^
	***************************************/
	FieldCursorSquare::FieldCursorSquare() :
		cntFrame(FadeDuration)
	{
		transform = new Transform();

		//XZ���ʂɑ΂��ĕ��s�ɂȂ�悤�ɉ�]
		transform->Rotate(90.0f, 0.0f, 0.0f);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Field/CursorSquare.png");

		//�T�C�Y�ݒ�
		SetSize(Size);
	}

	/**************************************
	FieldCursorSquare�f�X�g���N�^
	***************************************/
	FieldCursorSquare::~FieldCursorSquare()
	{
		SAFE_DELETE(transform);
	}

	/**************************************
	FieldCursorSquare�X�V����
	***************************************/
	void FieldCursorSquare::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//������Ɉړ�
		transform->Move(Vector3::Up * MoveSpeed);

		//�}�e���A���̓��ߗ���ݒ�
		float t = (float)cntFrame / FadeDuration;
		material.Diffuse.a = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InExpo);
	}

	/**************************************
	FieldCursorSquare�`�揈��
	***************************************/
	void FieldCursorSquare::Draw(const D3DXMATRIX& parentMtx)
	{
		if (!IsActive())
			return;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//���[���h�ϊ��ݒ�
		transform->SetWorld(&parentMtx);

		//�`��
		BoardPolygon::Draw();
	}

	/**************************************
	FieldCursorSquare�Z�b�g����
	***************************************/
	void FieldCursorSquare::Set()
	{
		cntFrame = 0;
		transform->SetPosition(Vector3::Zero);
	}

	/**************************************
	FieldCursorSquare�A�N�e�B�u����
	***************************************/
	bool FieldCursorSquare::IsActive()
	{
		return cntFrame < FadeDuration;
	}

	/**************************************
	FieldCursorSquare��r���Z�q
	***************************************/
	bool FieldCursorSquare::Compare(const FieldCursorSquare * lhs, const FieldCursorSquare * rhs)
	{
		return lhs->cntFrame < rhs->cntFrame;
	}
}