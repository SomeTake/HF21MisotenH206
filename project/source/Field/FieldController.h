//=====================================
//
//FieldController.h
//�@�\:�t�B�[���h�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCONTROLLER_H_
#define _FIELDCONTROLLER_H_

#include "../../main.h"

class ItemModel;

namespace Field
{
	/**************************************
	�O���錾
	***************************************/
	class FieldCursor;
	class FieldGround;
	
	namespace Model
	{
		class PlaceContainer;
	}

	/**************************************
	�N���X��`
	***************************************/
	class FieldController
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		FieldController();
		~FieldController();

		//�X�V�A�`�揈��
		void Update();
		void Draw();

		//�f�[�^�ǂݍ��ݏ���
		//TODO:�ǂݍ��ރf�[�^��I���ł���悤�ɂ���
		void Load();

		//���͊m�F����
		void CheckInput();

		//�J�[�\���擾����
		GameObject* GetFieldCursor();

	private:
		const float PlaceOffset = 10.0f;		//Place��1�}�X���̃I�t�Z�b�g�l
		const int InitFieldBorder = 25;			//�t�B�[���h�͈͂̏����l
		const int InputLongWait = 15;			//���̓��s�[�g�̑ҋ@�t���[��
		const int InputShortWait = 5;			//���̓��s�[�g�̑ҋ@�t���[��

		FieldCursor *cursor;					//�J�[�\��
		FieldGround *ground;					//�n��
		Model::PlaceContainer *placeContainer;	//�v���C�X�R���e�i
		ItemModel* item;						// �A�C�e�����f��

		int fieldBorder;						//�t�B�[���h�͈�(�}�X�P��)
		int inputRepeatCnt;						//���͂̃��s�[�g�J�E���g
	};
}
#endif