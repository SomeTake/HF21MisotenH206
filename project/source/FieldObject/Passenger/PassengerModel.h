//=====================================
//
// �p�b�Z���W���[���f��[PassengerModel.h]
// �@�\�F�p�b�Z���W���[�̃��f���N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PASSENGERMODEL_H_
#define _PASSENGERMODEL_H_

#include <vector>
#include <deque>

#include "PassengerActor.h"

//**************************************
// �N���X��`
//**************************************
class PassengerModel
{
private:
	PassengerActor* actor;
	std::deque<D3DXVECTOR3> route;					// �o���n�_����ړI�n�܂ł̍��W���i�[
	int current;									// 
	int nextDest;									// root�̓Y���Ƃ��Ďg�p

	void CheckCallback();							// �R�[���o�b�N�̊m�F

	std::function<void(const D3DXVECTOR3&)> *callbackToAlong;

public:
	PassengerModel(const std::deque<D3DXVECTOR3>& root, std::function<void(const D3DXVECTOR3&)> *callback);
	~PassengerModel();

	// �X�V�A�`��
	void Update();
	void Draw();

	// �g�p���m�F
	bool IsActive();

	// �A�N�^�[�̃Z�b�g
	void SetActor(const std::deque<D3DXVECTOR3>& root);

	D3DXVECTOR3 FindDestination();
};

#endif
