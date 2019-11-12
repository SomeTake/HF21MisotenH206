//=====================================
//
// ActorLoader.h
// �@�\:�A�N�^�[�̃��f�����[�_
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ACTORLOADER_H_
#define _ACTORLOADER_H_

#include "../../main.h"

#include <map>

namespace Field::Actor
{
	/**************************************
	�O���錾
	***************************************/

	/**************************************
	�N���X��`
	***************************************/
	class ActorLoader
	{
	public:
		const static std::string CityTag[];			//�X���f���̃��\�[�X�^�O
		const static std::string StraightTag[];		//�������̃��\�[�X�^�O
		const static std::string CurveTag[];		//�J�[�u���̃��\�[�X�^�O
		const static std::string TJunctionTag[];	//T���H�̃��\�[�X�^�O
		const static std::string CrossTag[];		//�\���H�̃��\�[�X�^�O
		const static std::string BridgeTag[];		//���̃��\�[�X�^�O
		const static std::string MountainTag[];		//�R�̃��\�[�X�^�O

		//�R���X�g���N�^�A�f�X�g���N�^
		ActorLoader();
		~ActorLoader();

		//�ݒ�t�@�C���̓ǂݍ���
		void LoadConfig();

		//���\�[�X�̓ǂݍ���
		void LoadResource();

	private:
		std::map<std::string, std::string> modelFileName;	//�^�O�ƃt�@�C�����̑Ή��}�b�v

	};
}



#endif