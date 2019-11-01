#ifndef _INFOCONTROLLER_H_
#define _INFOCONTROLLER_H_

#include <map>
#include "Infomation/LinkInfoActor.h"
#include "../Field/FieldConfig.h"

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
	void SetLinkLevel(const Field::FieldPosition& key, const int& townLevel);
};

#endif
