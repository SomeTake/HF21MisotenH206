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

/**************************************
�O���錾
***************************************/
namespace Field::Model
{
	class PlaceModel;
}

/**************************************
�N���X��`
***************************************/
class FieldEventHandler
{
public:
	FieldEventHandler();
	~FieldEventHandler();

	void AdjustLevelAI(float percent);
	void AddLevelAI(float num);
	void AdjustAllLinkLevel(int num);
	void AdjustLinkLevel(int num);
	void AddStockNum(int num);
	void SetDevelopBonus(float percent);
	void CreateNewTown();
	void DestroyTown(const Field::Model::PlaceModel* place);
	void ReverseOperation(bool isReverse);
	void SealUsingItem(bool isSeal);
	void RaiseTrafficJam(float bias);
	void RecoveryRemainTime(int frame);
	bool TryUsingEDF();
	bool TryUsingInsurance();
	void PauseGame();
	void ResumeGame();
	const Field::Model::PlaceModel* GetDestroyTarget();

private:

};

#endif