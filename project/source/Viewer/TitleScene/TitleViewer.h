//=====================================
//
// �^�C�g���r���A�[[TitleViewer.h]
// �@�\�F�^�C�g�����UI�\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _TITLEVIEWER_H_
#define _TITLEVIEWER_H_

//**************************************
// �N���X��`
//**************************************
class TitleViewer
{
private:
	bool isActive;

public:
	TitleViewer();
	~TitleViewer();

	void Update();
	void Draw();

	void SetActive();
};

#endif
