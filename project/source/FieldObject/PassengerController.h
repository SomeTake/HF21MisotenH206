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
	//�R���X�g���N�^�œ��������f���ւ̃R�[���o�b�N��n��
	PassengerController();
	~PassengerController();

	// �X�V�A�`��
	void Update();
	void Draw();

	// �p�b�Z���W���[�Z�b�g
	void SetPassenger(std::vector<D3DXVECTOR3>& root);

	//�p�b�Z���W���[���v���C�X�ɓ��B�����ۂ̃R�[���o�b�N���ݒ肳���
	void SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback);

private:
	std::vector<PassengerModel*> modelVector;

	std::function<void(const D3DXVECTOR3&)> callback;

	static const int PassengerReserve;
};


#endif
