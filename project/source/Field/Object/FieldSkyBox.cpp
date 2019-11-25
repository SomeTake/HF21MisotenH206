//=====================================
//
//�t�B�[���h�X�J�C�{�b�N�X����[FieldSkyBox.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "FieldSkyBox.h"
#include "../../../Framework/Resource/ResourceManager.h"

namespace Field
{
	/**************************************
	static�����o
	***************************************/
	const char* FieldSkyBox::CityTexturePath[] = {
		"data/TEXTURE/Skybox/Sunny_01A_up.png",
		"data/TEXTURE/Skybox/Sunny_01A_back.png",
		"data/TEXTURE/Skybox/Sunny_01A_down.png",
		"data/TEXTURE/Skybox/Sunny_01A_front.png",
		"data/TEXTURE/Skybox/Sunny_01A_left.png",
		"data/TEXTURE/Skybox/Sunny_01A_right.png"
	};

	const char* FieldSkyBox::WorldTexturePath[] = {
		"data/TEXTURE/Skybox/WorldSkyBox02bUp.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bBack.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bDown.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bFront.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bLeft.jpg",
		"data/TEXTURE/Skybox/WorldSkyBox02bRight.jpg",
	};

	const char* FieldSkyBox::SpaceTexturePath[] = {
		"data/TEXTURE/Skybox/SpaceUp_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceBack_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceDown_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceFront_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceRight_Tex.jpg",
		"data/TEXTURE/Skybox/SpaceLeft_Tex.jpg",
	};

	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldSkyBox::FieldSkyBox(Field::FieldLevel level) :
		SkyBox({ 20000.0f, 20000.0f, 20000.0f })
	{
		//�e�N�X�`���ǂݍ���
		switch (level)
		{
		case FieldLevel::City:
			for (int i = 0; i < Surface::Max; i++)
			{
				LoadTexture(CityTexturePath[i], (Surface)i);
			}
			break;

		case FieldLevel::World:
			for (int i = 0; i < Surface::Max; i++)
			{
				LoadTexture(WorldTexturePath[i], (Surface)i);
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

	/**************************************
	���\�[�X�ǂݍ��ݏ���
	***************************************/
	void FieldSkyBox::LoadResource()
	{
		for (int i = 0; i < Surface::Max; i++)
		{
			ResourceManager::Instance()->LoadTexture(CityTexturePath[i]);
			ResourceManager::Instance()->LoadTexture(WorldTexturePath[i]);
			ResourceManager::Instance()->LoadTexture(SpaceTexturePath[i]);
		}
	}
}