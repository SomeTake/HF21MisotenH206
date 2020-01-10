//=====================================
//
//SuspendViewer.h
//�@�\:�T�X�y���h�r���[���[
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SUSPENDVIEWER_H_
#define _SUSPENDVIEWER_H_

#include "../../../../main.h"
#include "../../../../Framework/Renderer2D/Polygon2D.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SuspendViewer : public Polygon2D
{
public:
	enum Dialog
	{
		Yes,
		No,
		DialogMax
	};

	SuspendViewer();
	~SuspendViewer();

	void Update();
	void Draw();
	
	Dialog GetSelected() const;

private:
	Polygon2D *dialogYes, *dialogNo;
	Polygon2D *bg;

	bool selectedYes;
};
#endif