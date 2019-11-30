//=====================================
//
// �l�[���r���A�[[NameViewer.h]
// �@�\�F���O�\���p
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _NAMEVIEWER_H_
#define _NAMEVIEWER_H_

#include "../../../main.h"
#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Renderer2D/Polygon2D.h"

//**************************************
// �N���X��`
//**************************************
class NameViewer
{
public:
	NameViewer();
	~NameViewer();

	void Update();
	void Draw();

	// �������W�A�T�C�Y�̐ݒ�
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

	// ���O���Z�b�g�i�z��̐擪�|�C���^������AInit���Ăяo���Ă���g�p����j
	void SetName(int* Buff);

	void SetSize(const float& x, const float& y);
	void SetPosition(const D3DXVECTOR3& pos);

private:
	static const int NumChar = 3;	// ������
	static const int DivideX = 6;	// �e�N�X�`��������
	static const int DivideY = 6;	// �e�N�X�`��������
	inline static float Width = 1.0f / 6.0f;
	inline static float Height = 1.0f / 6.0f;

	Polygon2D* polygon[NumChar];
	D3DXVECTOR3 stdPosition;		// ��ɂȂ���W�i���S�̕����̒��S�j
	float interval;					// �����̊Ԃ̋���
};


#endif