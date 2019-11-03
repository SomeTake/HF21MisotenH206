//=====================================
//
// FieldSkyBox.h
// �@�\:�t�B�[���h�X�J�C�{�b�N�X
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDSKYBOX_H_
#define _FIELDSKYBOX_H_

#include "../../../main.h"
#include "../../../Framework/Renderer3D/SkyBox.h"
#include "../FieldConfig.h"

namespace Field
{
	/**************************************
	�O���錾
	***************************************/

	/**************************************
	�N���X��`
	***************************************/
	class FieldSkyBox : public SkyBox
	{
	public:
		FieldSkyBox(Field::FieldLevel level);

	private:
		static const char* CityTexturePath[];
		static const char* WorldTexturePath[];
		static const char* SpaceTexturePath[];
	};
}

#endif