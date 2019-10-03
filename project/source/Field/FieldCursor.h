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
		FieldCursor();
		~FieldCursor();

		//�X�V�����A�`�揈��
		void Update();
		void Draw();

		//�ړ�����
		void Move(const D3DXVECTOR3& direction);

		//�ړ��͈͐ݒ菈��
		void SetBorder(float borderX, float borderZ);

	private:
		const int SquareMax = 5;			//�l�p�`�ő吔
		const int EmitInterval = 10;		//�l�p�`�����C���^�[�o��
		const int MoveDuration = 4;			//�ړ�����

		float borderX, borderZ;				//�ړ��\�͈�
		int cntFrame;						//�t���[���J�E���g

		std::vector<FieldCursorSquare*> squareContainer;	//�l�p�`�R���e�i

		//�l�p�`�Z�b�g����
		void SetSquare();
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
		const D3DXVECTOR2 Size{ 5.0f, 5.0f };		//�T�C�Y
		const int FadeDuration = 30;				//�t�F�[�h����
		const float MoveSpeed = 0.3f;				//�ړ��X�s�[�h

		int cntFrame;					//�t���[���J�E���g
		Transform *transform;			//SRT���
	};
}

#endif