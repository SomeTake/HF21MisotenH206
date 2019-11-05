
//=============================================================================
//
// �t�B�[���h�e���b�v���� [FieldTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _FIELD_TELOP_H_
#define _FIELD_TELOP_H_

#include "../../Framework/BaseViewer.h"
#include "../../../../Framework/Pattern/Delegate.h"
#include <vector>
#include <functional>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class BaseViewerDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FieldTelop :public BaseViewer
{
public:
	FieldTelop();
	~FieldTelop();

	//�e���b�v�̎��
	enum TelopID
	{
		City,
		Max
	};

	void Update();
	void Draw(void);
	void Set(TelopID id, std::function<void(void)> Callback = nullptr);

private:
	BaseViewerDrawer *text;
	BaseViewerDrawer *line;

	//�Đ��I���ʒm
	std::function<void(void)> Callback;

	//�e�L�X�g�̃e�N�X�`�����R���e�i
	std::vector <LPDIRECT3DTEXTURE9> textTexContainer;

	//�w�i�̃e�N�X�`�����R���e�i
	std::vector <LPDIRECT3DTEXTURE9> bgTexContainer;

	//�Đ�
	void Play();

	//�e�N�X�`�����󂯓n��
	void PassTexture(TelopID id);

	//��������
	void DrawLine(void);

	//�t�F�[�h�A�E�g
	void FadeOut(void);

	//�Đ������ǂ���
	bool isPlaying;

	//�t���[���J�E���g
	int countFrame;

	//���݂̃A�j���[�V����
	int currentAnim;

	//�e�N�X�`���̃��l
	float alpha;

	//�A�j���[�V��������
	float animTime;
};

#endif