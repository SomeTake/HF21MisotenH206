//=====================================
//
// �l�[��[Name.h]
// �@�\�F�l�[���̃f�[�^��ۑ�����N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _NAME_H_
#define _NAME_H_

//**************************************
// �N���X��`
//**************************************
class Name
{
private:
	int num[3];

public:
	Name();
	Name(int first, int second, int third);
	~Name();

	// �R�s�[�R���X�g���N�^
	Name(const Name& in);

	void Set(int first, int second, int third);

	int Get(int No);
};

#endif
