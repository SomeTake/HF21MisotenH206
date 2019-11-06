//=====================================
//
//�t�B�[���C�x���g�n���h������[FieldEventHandler.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "FieldEventHandler.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
FieldEventHandler::FieldEventHandler()
{
	functerInt.resize(FuncterID_int::FuncterIntMax, nullptr);
	functerFloat.resize(FuncterID_float::FuncterFloatMax, nullptr);
	functerBool.resize(FuncterID_bool::FuncterBoolMax, nullptr);
	functerBoolReturn.resize(FuncterID_boolReturn::FuncterBoolReturnMax, nullptr);
	functerVoid.resize(FuncterID_void::FuncterVoidMax, nullptr);
	functerPlaceReturn.resize(FuncterID_PlaceReturn::FuncterPlaceReturnMax, nullptr);
	functerPlace.resize(FuncterID_Place::FuncterPlaceMax, nullptr);
}

/**************************************
�f�X�g���N�^
***************************************/
FieldEventHandler::~FieldEventHandler()
{
	functerInt.clear();
	functerFloat.clear();
	functerBool.clear();
	functerBoolReturn.clear();
	functerPlace.clear();
}

/**************************************
AI���W���x������
***************************************/
void FieldEventHandler::AdjustLevelAI(float percent)
{
	functerFloat[FuncterID_float::AdjustAI](percent);
}

/**************************************
AI���W���x�����Z
***************************************/
void FieldEventHandler::AddLevelAI(float num)
{
	functerFloat[FuncterID_float::AddAI](num);
}

/**************************************
�X�S�̂̃����N���x������
***************************************/
void FieldEventHandler::AdjustAllLinkLevel(int num)
{
	functerInt[FuncterID_int::AdjustLinkAll](num);
}

/**************************************
�X��̃����N���x������
***************************************/
void FieldEventHandler::AdjustLinkLevel(int num)
{
	functerInt[FuncterID_int::AdjustLink](num);
}

/**************************************
�X�g�b�N�����Z
***************************************/
void FieldEventHandler::AddStockNum(int num)
{
	functerInt[FuncterID_int::AddStock](num);
}

/**************************************
���W�{�[�i�X�ݒ�
***************************************/
void FieldEventHandler::SetDevelopBonus(float percent)
{
	functerFloat[FuncterID_float::SetDevBonus](percent);
}

/**************************************
�V�����X����
***************************************/
void FieldEventHandler::CreateNewTown(const Field::Model::PlaceModel* place)
{
	functerPlace[FuncterID_Place::Create](place);
}

/**************************************
�X�j�󏈗�
***************************************/
void FieldEventHandler::DestroyTown(const Field::Model::PlaceModel * place)
{
	functerPlace[FuncterID_Place::Destroy](place);
}

/**************************************
���씽�]����
***************************************/
void FieldEventHandler::ReverseOperation(bool isReverse)
{
	functerBool[FuncterID_bool::ReverseOpe](isReverse);
}

/**************************************
�X�g�b�N���󏈗�
***************************************/
void FieldEventHandler::SealUsingItem(bool isSeal)
{
	functerBool[FuncterID_bool::SealItem](isSeal);
}

/**************************************
���G�x��������
***************************************/
void FieldEventHandler::AdjustTrafficJam(float bias)
{
	functerFloat[FuncterID_float::AdjustTraffic](bias);
}

/**************************************
�������ԉ񕜏���
***************************************/
void FieldEventHandler::AddRemainTime(int frame)
{
	functerInt[FuncterID_int::AddTime](frame);
}

/**************************************
�n���h�q�R���g���邩
***************************************/
bool FieldEventHandler::TryUsingEDF()
{
	return functerBoolReturn[FuncterID_boolReturn::TryEDF]();
}

/**************************************
�ی����g���邩
***************************************/
bool FieldEventHandler::TryUsingInsurance()
{
	return functerBoolReturn[FuncterID_boolReturn::TryInsurance]();
}

/**************************************
�Q�[���i�s��~
***************************************/
void FieldEventHandler::PauseGame()
{
	functerVoid[FuncterID_void::Pause]();
	SetEventControllerInPause(true);
}

/**************************************
�Q�[���i�s�ĊJ
***************************************/
void FieldEventHandler::ResumeGame()
{
	functerVoid[FuncterID_void::Resume]();
	SetEventControllerInPause(false);
}

/**************************************
�j��Ώێ擾����
***************************************/
const Field::Model::PlaceModel * FieldEventHandler::GetDestroyTarget()
{
	return functerPlaceReturn[FuncterID_PlaceReturn::DestroyTarget]();
}

/**************************************
�V�����X�����Place�擾����
***************************************/
const Field::Model::PlaceModel * FieldEventHandler::GetNewTownPosition()
{
	return functerPlaceReturn[FuncterID_PlaceReturn::PlacePosition]();
}

/**************************************
�A�g�����e�B�X�ƂȂ�Place�̎擾
***************************************/
const Field::Model::PlaceModel * FieldEventHandler::GetAtlantisPlace()
{
	return functerPlaceReturn[FuncterID_PlaceReturn::Atlantis]();
}
