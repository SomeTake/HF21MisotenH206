//=============================================================================
//
// Field�r���A�[�Ǘ����� [FieldViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _FIELD_VIEWER_H_
#define _FIELD_VIEWER_H_

#include <vector>
#include "FieldTelop.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class FieldTelop;
class BaseViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FieldViewer
{
public:
	FieldViewer();
	~FieldViewer();

	void Update(void);
	void Draw(void);

	void SetFieldTelop(FieldTelop::TelopID id, std::function<void(void)> Callback);
	std::vector <BaseViewer*> fieldViewer;

private:
	FieldTelop * fieldTelop;
};

#endif

