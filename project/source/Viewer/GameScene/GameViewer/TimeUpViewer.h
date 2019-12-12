//=====================================
//
//TimeUpViewer.h
//�@�\:�^�C���A�b�v�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TIMEUPVIEWER_H_
#define _TIMEUPVIEWER_H_

#include "../../../../main.h"
#include "../../Framework/BaseViewer.h"
#include <functional>

/**************************************
�O���錾
***************************************/
class TextureDrawer;

/**************************************
�N���X��`
***************************************/
class TimeUpViewer : public BaseViewer
{
public:
	TimeUpViewer();
	~TimeUpViewer();

	void Update();
	void Draw();

	void Set(std::function<void()> callback = nullptr);

private:
	TextureDrawer *tex;

	int cntFrame;
	bool active;

	std::function<void()> callback;
};
#endif