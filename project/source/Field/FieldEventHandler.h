//=====================================
//
// FieldEventHandler.h
// �@�\:�t�B�[���C�x���g�n���h��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDEVENTHANDLER_H_
#define _FIELDEVENTHANDLER_H_

#include "../../main.h"

#include <functional>
#include <vector>

/**************************************
�O���錾
***************************************/
namespace Field::Model
{
	class PlaceModel;
}

namespace Field
{
	class FieldController;
}

/**************************************
�N���X��`
***************************************/
class FieldEventHandler
{
public:
	FieldEventHandler();
	~FieldEventHandler();

	void AdjustLevelAI(float percent);							//AI���W���x���̒�������
	void AddLevelAI(float num);									//AI���W���x�����Z����
	void AdjustAllLinkLevel(int num);							//�X�S�̂̃����N���x����������
	void AdjustLinkLevel(int num);								//�X��̃����N���x����������
	void AddStockNum(int num);									//�A�C�e���X�g�b�N���Z����
	void SetDevelopBonus(float percent);						//���W�x�{�[�i�X�ݒ菈��
	void CreateNewTown(const Field::Model::PlaceModel* place);	//�V�����X�쐬����
	void DestroyTown(const Field::Model::PlaceModel* place);	//�X�j�󏈗�
	void CreateAtlantis(const Field::Model::PlaceModel* place);	//�A�g�����e�B�X�o������
	void ReverseOperation(bool isReverse);						//���씽�]����
	void SealUsingItem(bool isSeal);							//�A�C�e���X�g�b�N���󏈗�
	void AdjustTrafficJam(float bias);							//���G�x��������
	void AddRemainTime(int frame);								//�������ԉ񕜏���
	bool TryUsingEDF();											//�n���h�q�R�X�g�b�N�̎g�p�۔���
	bool TryUsingInsurance();									//�ی��X�g�b�N�̎g�p�۔���
	void PauseGame();											//�Q�[�����f����
	void ResumeGame();											//�Q�[���ĊJ����
	const Field::Model::PlaceModel* GetDestroyTarget();			//�j��Ώۂ̊X�擾����
	const Field::Model::PlaceModel* GetNewTownPosition();		//�V�����X�����\���Place�擾
	const Field::Model::PlaceModel* GetAtlantisPlace();			//�A�g�����e�B�X�ƂȂ�Place�̎擾
	
private:
	//float�^�������ɂƂ�t�@���N�^�̒ʂ��ԍ�
	enum FuncterID_float
	{
		AdjustAI,
		AddAI,
		SetDevBonus,
		AdjustTraffic,
		FuncterFloatMax
	};

	//int�^�������Ɏ��t�@���N�^�̒ʂ��ԍ�
	enum FuncterID_int
	{
		AdjustLinkAll,
		AdjustLink,
		AddStock,
		AddTime,
		FuncterIntMax
	};

	//bool�^�������Ɏ��t�@���N�^�̒ʂ��ԍ�
	enum FuncterID_bool
	{
		ReverseOpe,
		SealItem,
		FuncterBoolMax
	};

	//���������Ȃ�bool��Ԃ��t�@���N�^�̒ʂ��ԍ�
	enum FuncterID_boolReturn
	{
		TryEDF,
		TryInsurance,
		FuncterBoolReturnMax
	};

	//���������Ȃ��t�@���N�^�̒ʂ��ԍ�
	enum FuncterID_void
	{
		Pause,
		Resume,
		FuncterVoidMax
	};

	//PlaceModel��Ԃ��t�@���N�^�̒ʂ��ԍ�
	enum FuncterID_PlaceReturn
	{
		DestroyTarget,
		PlacePosition,
		Atlantis,
		FuncterPlaceReturnMax
	};

	//PlaceModel�������ɂƂ�t�@���N�^�̒ʂ��ԍ�
	enum FuncterID_Place
	{
		Destroy,
		Create,
		SetAtlantis,
		FuncterPlaceMax
	};

	std::vector<std::function<void(float)>> functerFloat;
	std::vector<std::function<void(int)>> functerInt;
	std::vector<std::function<void(bool)>> functerBool;
	std::vector<std::function<bool(void)>> functerBoolReturn;
	std::vector<std::function<void(void)>> functerVoid;
	std::vector<std::function<const Field::Model::PlaceModel*(void)>> functerPlaceReturn;
	std::vector<std::function<void(const Field::Model::PlaceModel*)>> functerPlace;
	std::function<void(bool)> SetEventControllerInPause;

	friend class GameScene;
	friend class Field::FieldController;
	friend class EventController;
};

#endif