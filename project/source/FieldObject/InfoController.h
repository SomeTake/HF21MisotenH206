//=====================================
//
// �C���t�H�R���g���[��[InfoController.h]
// �@�\�FInfoActor�̃R���g���[���N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _INFOCONTROLLER_H_
#define _INFOCONTROLLER_H_

#include <map>
#include "Infomation/LinkInfoActor.h"
#include "../Field/FieldConfig.h"
#include "../Field/Place/PlaceConfig.h"

//**************************************
// �N���X��`
//**************************************
class InfoController
{
private:
	std::map<Field::FieldPosition, LinkInfoActor*> LinkInfoMap; // �����N���x���\���p

public:
	InfoController();
	~InfoController();

	void Update();
	void Draw();

	// ���̃����N���x���̃Z�b�g�A���x���A�b�v
	void SetLinkLevel(const Field::Model::PlaceData& data);
};

#endif
