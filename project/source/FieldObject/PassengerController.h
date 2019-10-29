//=====================================
//
// �p�b�Z���W���[�R���g���[��[PassengerController.h]
// �@�\�F�p�b�Z���W���[�Ǘ��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PASSENGERCONTROLLER_H_
#define _PASSENGERCONTROLLER_H_

#include "Passenger/PassengerModel.h"
#include <vector>
#include <functional>

//**************************************
// �N���X��`
//**************************************
class PassengerController
{
public:
	PassengerController();
	~PassengerController();

	// �X�V�A�`��
	void Update();
	void Draw();

	// �p�b�Z���W���[�Z�b�g
	void SetPassenger(std::vector<D3DXVECTOR3>& root);

private:
	std::vector<PassengerModel*> modelVector;

	static const int PassengerReserve;
};


#endif
