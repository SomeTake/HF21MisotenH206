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
	Field::FieldLevel current;
	std::map<Field::FieldPosition, LinkInfoActor*> LinkInfoMap; // �����N���x���\���p

	// ���̃����N���x���̃Z�b�g�A���x���A�b�v
	void SetLinkLevel(const Field::PlaceData& data);

public:
	InfoController(Field::FieldLevel currentLevel);
	~InfoController();

	void Update();
	void Draw();

	// �S�Ă̒��̃����N���x���̃Z�b�g�A���x���A�b�v
	void SetAllLinkLevel(const std::vector<Field::PlaceData>& vec);

	// ���Link���x���̍������̃��x���𒲂ׂ�
	int SearchMaxLinkLevel();
};

#endif
