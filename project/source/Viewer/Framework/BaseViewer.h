//=============================================================================
//
// ���Viewer���� [BaseViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BASE_VIEWER_H_
#define _BASE_VIEWER_H_

#include <functional>
//*****************************************************************************
// ���N���X��`
//*****************************************************************************
class BaseViewer
{
private:
	float currentParam = 0;
	float lastParam = 0;

public:
	BaseViewer() {};
	virtual ~BaseViewer() {}

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//���݃t���[���ƑO�t���[���̃p�����[�^���r���Č��ʂ�Ԃ�
	template <class T>
	bool isCurrentGreaterLast(const T param)
	{
		bool isGreater = false;

		currentParam = param;
		if (currentParam < lastParam)
		{
			isGreater = true;
		}
		lastParam = param;

		return isGreater;
	}
	template <class T>
	bool isCurrentSmallerLast(const T param)
	{
		bool isSmaller = false;

		currentParam = param;
		if (currentParam < lastParam)
		{
			isSmaller = true;
		}
		lastParam = param;

		return isSmaller;
	}

	//�Đ������ǂ���
	bool isPlaying;
};

#endif

