//=====================================
//
//WaterHeightController.cpp
//�@�\:���̐��ʃR���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "WaterHeightController.h"
#include "../../../Framework/Math/Easing.h"

/**************************************
static�����o
***************************************/
const int WaterHeightController::AnimationPeriod = 360;
const float WaterHeightController::MaxWaveHeight = 0.015f;

float WaterHeightController::heightWave = 0.0f;
int WaterHeightController::cntWaveAnimation = 0;

/**************************************
���ʍX�V����
***************************************/
void WaterHeightController::UpdateHeight()
{
	cntWaveAnimation = Math::WrapAround(0, AnimationPeriod, ++cntWaveAnimation);

	float startHeight = (cntWaveAnimation < AnimationPeriod / 2) ? -MaxWaveHeight : MaxWaveHeight;
	float goalHeight = startHeight * -1.0f;
	float t = (cntWaveAnimation < AnimationPeriod / 2) ? cntWaveAnimation / (AnimationPeriod * 0.5f) : (cntWaveAnimation - AnimationPeriod * 0.5f) / (AnimationPeriod * 0.5f);

	heightWave = Easing::EaseValue(t, startHeight, goalHeight, EaseType::InOutBack);
}