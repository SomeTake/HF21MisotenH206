//=====================================
//
//フィールドスカイボックス処理[FieldSkyBox.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "FieldSkyBox.h"

namespace Field
{
	/**************************************
	staticメンバ
	***************************************/
	const char* FieldSkyBox::CityTexturePath[] = {
		"data/TEXTURE/Skybox/Sunny_01A_up.png",
		"data/TEXTURE/Skybox/Sunny_01A_back.png",
		"data/TEXTURE/Skybox/Sunny_01A_down.jpg",
		"data/TEXTURE/Skybox/Sunny_01A_front.png",
		"data/TEXTURE/Skybox/Sunny_01A_left.png",
		"data/TEXTURE/Skybox/Sunny_01A_right.png"
	};

	const char* FieldSkyBox::SpaceTexturePath[] = {
		"data/TEXTURE/Skybox/SpaceUp_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceBack_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceDown_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceFront_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceLeft_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceRight_Tex.jpg",
	};

	/**************************************
	コンストラクタ
	***************************************/
	FieldSkyBox::FieldSkyBox(Field::FieldLevel level) :
		SkyBox({ 20000.0f, 20000.0f, 20000.0f })
	{
		//テクスチャ読み込み
		switch (level)
		{
		case FieldLevel::City:
			for (int i = 0; i < Surface::Max; i++)
			{
				LoadTexture(CityTexturePath[i], (Surface)i);
			}
			break;

		case FieldLevel::Space:
			for (int i = 0; i < Surface::Max; i++)
			{
				LoadTexture(SpaceTexturePath[i], (Surface)i);
			}
			break;	
		}
	}
}