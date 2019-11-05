//=====================================
//
//FieldCursor.cpp
//�@�\:�t�B�[���h�J�[�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCursor.h"
#include "../../../Framework/Math/Easing.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Resource/ResourceManager.h"

#include <algorithm>

namespace Field
{
	/**************************************
	static�ϐ�
	***************************************/
	const D3DXVECTOR2 FieldCursorSquare::Size = { 6.5f, 6.5f };
	const int FieldCursorSquare::FadeDuration = 40;
	const float FieldCursorSquare::MoveSpeed = 0.45f;

	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldCursor::FieldCursor(float positionOffset) :
		PositionOffset(positionOffset),
		fieldBorder(0, 0, 0, 0),
		position(0, 0),
		cntMove(MoveDuration),
		currentMode(Mode::BuildRoad)
	{
		//���\�[�X�쐬
		ResourceManager::Instance()->MakePolygon("CursorSquare", "data/TEXTURE/Field/CursorSquare.png", FieldCursorSquare::Size, { 2.0f, 1.0f });

		//�l�p�`����
		squareContainer.resize(SquareMax);
		for (auto&& square : squareContainer)
		{
			square = new FieldCursorSquare();
			ResourceManager::Instance()->GetPolygon("CursorSquare", square);
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
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		std::sort(squareContainer.begin(), squareContainer.end(), &FieldCursorSquare::Compare);

		for (auto&& square : squareContainer)
		{
			square->SetTextureIndex(currentMode);
			square->Draw(mtxWorld);
		}

		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	/**************************************
	�ړ�����
	***************************************/
	void FieldCursor::Move(int x, int z)
	{
		if (x == 0 && z == 0)
			return;

		if (cntMove < MoveDuration)
			return;

		//�ړ��J�n�n�_��ۑ�
		startPos = position.ConvertToWorldPosition();

		//X���̈ړ���D�悵�Ďg�p(Clamp�ňړ��͈͂𐧌�)
		if (x != 0)
			position.x = Math::Clamp(fieldBorder.left,  fieldBorder.right, position.x + x);
		else
			position.z = Math::Clamp(fieldBorder.back, fieldBorder.forward, position.z + z);

		//�ړ�����W���v�Z
		moveTarget = position.ConvertToWorldPosition();

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

		SetPosition(position.ConvertToWorldPosition());
	}

	/**************************************
	���[�h�؂�ւ�����
	***************************************/
	void Field::FieldCursor::SetMode(Mode mode)
	{
		currentMode = mode;
	}

	/**************************************
	�ړ������ǂ���
	***************************************/
	bool Field::FieldCursor::IsMoving() const
	{
		return cntMove <= MoveDuration;
	}

	/**************************************
	�ړ��͈͐ݒ菈��
	***************************************/
	void FieldCursor::SetBorder(int forward, int right, int back, int left)
	{
		fieldBorder = FieldBorder(forward, right, back, left);
	}

	/**************************************
	���W�擾����
	***************************************/
	FieldPosition FieldCursor::GetModelPosition() const
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
	FieldCursorSquare�R���X�g���N�^
	***************************************/
	FieldCursorSquare::FieldCursorSquare() :
		cntFrame(FadeDuration)
	{
		transform = new Transform();

		//�e�N�X�`����X������2����
		SetTexDiv({ 2.0f, 1.0f });

		//XZ���ʂɑ΂��ĕ��s�ɂȂ�悤�ɉ�]
		transform->Rotate(90.0f, 0.0f, 0.0f);
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
		float alpha = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InExpo);
		SetDiffuse({ 1.0f, 1.0f, 1.0f, alpha });
	}

	/**************************************
	FieldCursorSquare�`�揈��
	***************************************/
	void FieldCursorSquare::Draw(const D3DXMATRIX& parentMtx)
	{
		if (!IsActive())
			return;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//���[���h�ϊ��s����v�Z
		D3DXMATRIX world = transform->GetMatrix();
		D3DXMatrixMultiply(&world, &world, &parentMtx);

		//�`��
		BoardPolygon::Draw(world);
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