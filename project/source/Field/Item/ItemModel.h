//=====================================
//
// �A�C�e�����f��[ItemModel.h]
// �@�\�F�t�B�[���h��̃A�C�e�����f��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _ITEMMODEL_H_
#define _ITEMMODEL_H_

//**************************************
// �}�N����`
//**************************************

//**************************************
// �N���X��`
//**************************************
class ItemActor;
class ItemModel
{
private:
	ItemActor* actor;

public:
	ItemModel();
	~ItemModel();

	void Update();
	void Draw();
};

#endif
