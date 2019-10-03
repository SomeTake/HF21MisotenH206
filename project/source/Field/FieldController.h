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

class PlaceModel;

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

		FieldCursor *cursor;					//�J�[�\��
		FieldGround *ground;					//�n��
		Model::PlaceContainer *placeContainer;	//�v���C�X�R���e�i
		::PlaceModel *model;					//3D���f���}�l�[�W��(�e�X�g�p�j	

		int fieldBorder;						//�t�B�[���h�͈�(�}�X�P��)
	};
}
#endif