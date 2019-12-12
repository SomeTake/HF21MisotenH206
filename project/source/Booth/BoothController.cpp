//=====================================
//
//BoothController.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BoothController.h"
#include "../../Framework/Serial/SerialWrapper.h"

/**************************************
����������
***************************************/
void BoothController::Init()
{
	serial = new SerialWrapper(3);
	serial->Begin(9600);
}

/**************************************
�擾����
***************************************/
void BoothController::Uninit()
{
	SAFE_DELETE(serial);
}

/**************************************
��]����
***************************************/
void BoothController::RotateTable(unsigned char angle)
{
	size_t numPut = serial->Write(angle);
}

/**************************************
LED�_�ŏ���
***************************************/
void BoothController::BlinkLED(bool isPlus)
{
	if (isPlus)
		serial->Write('p');
	else
		serial->Write('m');
}
