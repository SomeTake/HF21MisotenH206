//=====================================
//
//WaterHeightController.h
//�@�\:���̐��ʃR���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _WATERHEIGHTCONTROLLER_H_
#define _WATERHEIGHTCONTROLLER_H_

#include "../../../main.h"

/**************************************
�N���X��`
***************************************/
class WaterHeightController
{
public:
	//�����X�V����
	static void UpdateHeight();

	//�����擾����
	static float GetHeight()
	{
		return heightWave;
	}

private:
	static const int AnimationPeriod;
	static const float MaxWaveHeight;

	static float heightWave;
	static int cntWaveAnimation;
};
#endif