//=====================================
//
// PlayerPrefs.h
// �@�\:�f�[�^�ۑ��@�\
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERPREFS_H_
#define _PLAYERPREFS_H_

#include <string>
#include <unordered_map>
#include <fstream>

#include "../../Library/nameof/nameof.hpp"
#include "../../Library/picojson/picojson.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class PlayerPrefs
{
public:

	/*********************************************
	�ۑ������f�[�^�̎擾����
	*********************************************/
	//bool�^
	static bool GetBool(const std::string& key);

	//int�^
	static int GetInt(const std::string& key);

	//float�^
	static float GetFloat(const std::string& key);

	//string�^
	static std::string GetString(const std::string& key);

	/*********************************************
	�f�[�^�̕ۑ�����
	*********************************************/
	template<class T>
	static void Save(const std::string& key, const T& value)
	{
		std::ifstream ifs;
		ifs.open(FileName, std::ios::binary);

		if (ifs.is_open())
		{
			picojson::value val;
			ifs >> val;
			ifs.close();

			picojson::object obj = val.get<picojson::object>();
			val.get<picojson::object>()[key] = picojson::value(value);

			std::string serializeData = val.serialize();
			std::ofstream ofs;
			ofs.open(FileName, std::ios::out);
			ofs << serializeData << std::endl;
			ofs.close();
		}
		else
		{
			Initialize(key, value);
		}
	}

private:
	PlayerPrefs();
	
	//����������
	template<class T>
	void Initialize(const std::string& key, T value)
	{
		picojson::object data;
		data.emplace(key, picojson::value(value));

		std::string serializeData = picojson::value(data).serialize();
		std::ofstream ofs;
		ofs.open(FileName, std::ios::out);
		ofs << serializeData << std::endl;
		ofs.close();
	}

	//JSON�擾����
	static picojson::value GetData(const std::string& key);

	static const char* FileName;
};

#endif