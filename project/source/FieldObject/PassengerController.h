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
#include <deque>
#include <functional>
#include <map>
#include "../Field/Place/FieldPlaceContainer.h"

//**************************************
// �N���X��`
//**************************************
class PassengerController
{
public:
	//�C�Ȃ̂����Ȃ̂�
	enum Geography
	{
		Ground,
		Sea
	};

	//�R���X�g���N�^�œ��������f���ւ̃R�[���o�b�N��n��
	PassengerController(Field::FieldLevel level);
	~PassengerController();

	// �X�V�A�`��
	void Update();
	void Draw();

	// ���\�[�X�ǂݍ���
	void LoadResource();

	// CSV�ǂݍ���
	void LoadCSV(const char* path);

	// �p�b�Z���W���[�Z�b�g
	void SetPassenger(std::deque<D3DXVECTOR3>& root);

	//�p�b�Z���W���[���v���C�X�ɓ��B�����ۂ̃R�[���o�b�N���ݒ肳���
	void SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback);

	// PlaceActor�ɍ��킹�ăp�b�Z���W���[�̎�ނ�؂�ւ��iFieldLevel = World�ł̂ݎg�p�j
	void CheckPassengerMesh();

	// ��or�C�̃f�[�^��������������ꍇ��������Ăяo��
	void RewriteMap(const Field::FieldPosition& pos, const Geography& data);

private:
	std::vector<PassengerModel*> modelVector;
	std::function<void(const D3DXVECTOR3&)> callback;
	std::map<Field::FieldPosition, int> continentMap;	// ��or�C���ʗp�}�b�v�iFieldLevel = World�ł̂ݎg�p�j
	int mapRowMax;
	int mapColumMax;
	Field::FieldLevel currentLevel;
	bool initializedMap;

	static const int PassengerReserve;

};


#endif
