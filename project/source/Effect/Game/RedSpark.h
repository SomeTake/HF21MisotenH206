//=============================================================================
//
// �Ԃ��X�p�[�N�G�t�F�N�g�N���X [RedSpark.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _RedSpark_H_
#define _RedSpark_H_

#include "../../../main.h"
#include "../../Viewer/Framework/ViewerDrawer/BaseViewerDrawer.h"
#include <vector>

namespace Effect::Game
{
	/**************************************
	RedSpark�N���X
	***************************************/
	class RedSpark : public BaseViewerDrawer
	{
	private:

	public:
		RedSpark();
		void Update();

	};

	/**************************************
	RedSparkController�N���X
	***************************************/
	class RedSparkController
	{
	private:
		std::vector<RedSpark*> SparkEffect;

	public:
		RedSparkController();
	};
}
#endif