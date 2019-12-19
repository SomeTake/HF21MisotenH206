//=====================================
//
//PlaceContainer.h
//�@�\:�v���C�X�R���e�i
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLACECONTAINER_H_
#define _PLACECONTAINER_H_

#include "../../../main.h"
#include "PlaceConfig.h"
#include "../FieldConfig.h"

#include <vector>
#include <unordered_map>
#include <functional>

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class PlaceModel;
	class TownModel;
	class JunctionModel;

	using JunctionContainer = std::unordered_map<unsigned, JunctionModel*>;
	using TownContainer = std::unordered_map<unsigned, TownModel*>;
	using TownAction = std::function<void(const PlaceModel *start, const PlaceModel *goal, const PlaceModel* town)>;
	using MorphAction = std::function<void(const PlaceModel*, int current, int next)>;

	/**************************************
	�N���X��`
	***************************************/
	class PlaceContainer
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		PlaceContainer();
		~PlaceContainer();

		//�X�V�����A�`�揈��
		void Update();

		//�N���A����
		void Clear();

		//�w�肵���}�X�ڂ�PlaceModel���擾
		PlaceModel* GetPlace(int x, int z);
		PlaceModel* GetPlace(const FieldPosition& position);

		//�SPlaceModel�擾����
		std::vector<PlaceModel*> GetAllPlaces() const;

		//CSV�f�[�^�ǂݍ���
		void LoadCSV(const char* filePath);

		//�v���C�X�̍s�Ɨ�̍ő吔�擾
		FieldPosition GetPlaceBorder() const;

		//�X�����ƌq�������Ƃ��ɌĂ΂�鏈��
		void OnConnectedTown(const PlaceModel* place, const PlaceModel *gate);

		//�����_�����ꂽ�ۂɌĂ΂�鏈��
		void OnCreateJunction(const PlaceModel* place);

		//�����N���x�����v�Z
		void CalcLinkLevel();

		//AI���W���x���v�Z
		float CalcDevelopmentLevelAI(float bonus);

		//�X�S�̂̃����N���x�������Z
		void AddAllLinkLevel(int num);
		
		//��̊X�̃����N���x�������Z
		void AddLinkLevel(int num);

		//���G�x�����o�C�A�X��ݒ�
		void SetTrafficjamBias(float bias);

		//�j��Ώۂ̃v���C�X�擾
		const PlaceModel* GetDestroyTarget();

		//�X������v���C�X�擾
		const PlaceModel* GetNonePlace(std::vector<PlaceModel*>* ignoreList = nullptr);

		//�X�j�󏈗�
		void DestroyTown(const PlaceModel* target);

		//�X�쐬����
		void CreateTown(const PlaceModel* target);

		//�A�g�����e�B�X�쐬����
		std::vector<const PlaceModel*> CreateAtlantis(const PlaceModel* target);

		//�p�b�Z���W���[�o���t�@���N�^�ݒ�
		void SetDepartPassengerFanctor(const TownAction& action);

		//���[�t�B���O�t�@���N�^�ݒ�
		void SetMorphingFantor(const MorphAction& action);

		//���ׂĂ̒��̔��W���x�����擾����
		std::vector<PlaceData> GetAllTownLevel();

		//�����N���x���擾
		int GetLinkLevel();

		// �q���������̐����擾
		int GetTownNum(void) { return this->townContainer.size(); };

#ifdef DEBUG_PLACEMODEL
		void DrawDebug();
#endif

	private:
		const int PlaceMax = 10000;				//�v���C�X�̍ő吔

		std::vector<PlaceModel*> placeVector;	//PlaceModel�R���e�i
		TownContainer townContainer;			//TownModel�R���e�i
		JunctionContainer junctionContainer;	//JunctionModel�R���e�i

		int placeRowMax;						//1�s������̃v���C�X�ő吔
		int placeColumMax;						//1�񂠂���̃v���C�X�ő吔

		int fieldLinkLevel;						//�STown�̃����N���x���̍��v

		bool initialized;						//�������t���O

		float trafficJamRate;					//���G�x
		float trafficJamBias;					//���G�x�o�C�A�X

		TownAction onDepartPassenger;			//�X����p�b�Z���W���[���o�鎞�ɌĂԃt�@���N�^
		MorphAction onStartMorph;				//���[�t�B���O�J�n�t�@���N�^

		//�אڃv���C�X�쐬��������
		void MakeAdjacency();
	};
}

#endif