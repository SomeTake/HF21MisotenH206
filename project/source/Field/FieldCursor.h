//=====================================
//
//FieldCursor.h
//�@�\:�t�B�[���h�J�[�\��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCURSOR_H_
#define _FIELDCURSOR_H_

#include <vector>

#include "../../main.h"
#include "FieldConfig.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"

namespace Field
{
/**************************************
�O���錾
***************************************/
	class FieldCursorSquare;

	/**************************************
	FieldCursor�N���X
	***************************************/
	class FieldCursor : public GameObject
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		FieldCursor(float positionOffset);
		~FieldCursor();

		//�X�V�����A�`�揈��
		void Update();
		void Draw();

		//�ړ�����
		void Move(int x, int z);

		//�ړ��͈͐ݒ菈��
		void SetBorder(int forward, int right, int back, int left);

		//���W�擾
		FieldPosition GetModelPosition() const;

		//���W�ݒ菈��
		void SetModelPosition(int x, int z);

	private:
		const int SquareMax = 5;			//�l�p�`�ő吔
		const int EmitInterval = 10;		//�l�p�`�����C���^�[�o��
		const int MoveDuration = 4;			//�ړ�����
		const float PositionOffset;			//1�}�X���̍��W�I�t�Z�b�g			

		int cntFrame;						//�t���[���J�E���g
		int cntMove;						//�ړ��J�E���g

		FieldPosition position;				//���W
		FieldBorder fieldBorder;			//�ړ��\�Ȕ͈�

		D3DXVECTOR3 moveTarget;				//�ړ��̖ڕW�n�_
		D3DXVECTOR3 startPos;				//�ړ��̃X�^�[�g�n�_

		std::vector<FieldCursorSquare*> squareContainer;	//�l�p�`�R���e�i

		//�l�p�`�Z�b�g����
		void SetSquare();

		//�ړ���������
		void Move();

		//���[���h���W�n�_����
		D3DXVECTOR3 CalcWorldPosition() const;
	};

	/**************************************
	FieldCursorSquare�N���X
	***************************************/
	class FieldCursorSquare : public BoardPolygon
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		FieldCursorSquare();
		~FieldCursorSquare();

		//�X�V�����A�`�揈��
		void Update();
		void Draw(const D3DXMATRIX& parentMtx);

		//�Z�b�g����
		void Set();

		//�A�N�e�B�u����
		bool IsActive();

		//��r�֐�
		static bool Compare(const FieldCursorSquare* lhs, const FieldCursorSquare* rhs);

	private:
		static const D3DXVECTOR2 Size;				//�T�C�Y
		static const int FadeDuration;				//�t�F�[�h����
		static const float MoveSpeed;				//�ړ��X�s�[�h

		int cntFrame;								//�t���[���J�E���g
		Transform *transform;						//SRT���
	};
}

#endif