//=====================================
//
//PlaceConfig.h
//�@�\:�v���C�X�ݒ�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLACECONFIG_H_
#define _PLACECONFIG_H_

namespace Field::Model
{
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
		Moutain			//�R
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
			return PlaceType::Moutain;

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
		Max
	};
}
#endif