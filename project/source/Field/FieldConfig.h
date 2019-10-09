//=====================================
//
//FieldConfig.h
//�@�\:�t�B�[���h�֘A�̐ݒ�l
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCONFIG_H_
#define _FIELDCONFIG_H_


namespace Field
{		
	/**************************************
	PlaceModel�̍��W�\����
	***************************************/
	struct FieldPosition
	{
		int x, z;

		FieldPosition()
		{
			x = 0;
			z = 0;
		}

		FieldPosition(int x, int z)
		{
			this->x = x;
			this->z = z;
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
}

#endif