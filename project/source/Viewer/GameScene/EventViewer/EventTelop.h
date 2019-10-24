
//=============================================================================
//
// �C�x���g�e���b�v���� [EventTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_TELOP_H_
#define _EVENT_TELOP_H_

#include "../../Framework/BaseViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include <vector>
#include <functional>

//�e���b�v�̎��
enum TelopID
{
	PositiveEvent01,
	PositiveEvent02,
	NegativeEvent01,
	NegativeEvent02
};

//*****************************************************************************
// �O���錾
//*****************************************************************************
class TelopDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventTelop :public BaseViewer
{
public:
	//�e���b�v�̎��ID
	//enum TelopID
	//{
	//	PositiveEvent01,
	//	PositiveEvent02,
	//	NegativeEvent01,
	//	NegativeEvent02
	//};

	EventTelop();
	~EventTelop();

	//�e���b�v�̎�ސ�
	static const int typeMax = 4;

	void Update();
	void Draw(void);
	void Set(TelopID id, std::function<void(void)> FinishFunc = nullptr);

private:
	TelopDrawer *text;
	TelopDrawer *bg;

	//�Đ��I���ʒm
	std::function<void(void)> FinishFunc;

	//�e�L�X�g�̃e�N�X�`�����R���e�i
	std::vector <LPDIRECT3DTEXTURE9> textTexContainer;
	//�w�i�̃e�N�X�`�����R���e�i
	std::vector <LPDIRECT3DTEXTURE9> bgTexContainer;

	//�Đ�
	void Play();

	//�e�N�X�`�����󂯓n��
	void PassTexture(TelopID id);
};

#endif