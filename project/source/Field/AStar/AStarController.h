//=====================================
//
//AStarController.h
//�@�\:A*�A���S���Y���̃R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ASTARCONTROLLER_H_
#define _ASTARCONTROLLER_H_

#include "../../../main.h"
#include "../Place/PlaceConfig.h"
#include "../FieldConfig.h"

#include <vector>
#include <deque>
#include <map>
#include <list>

/**************************************
�O���錾
***************************************/
namespace Field::Model
{
	class PlaceModel;
}

namespace Field::Route
{
	/**************************************
	AStar�m�[�h�N���X
	***************************************/
	class AStarNode
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		AStarNode(const Field::Model::PlaceModel* place);
		~AStarNode();

		//�X�R�A�擾
		int GetScore() const;

		//���R�X�g�擾
		int GetCost() const;

		//�q���[���X�e�B�b�N�R�X�g�v�Z
		void CalcHeuristicCost(const Field::FieldPosition& goal);

		//�I�[�v������
		void Open(AStarNode *parent, int realCost);

		//�ړ��\�Ȕ͈͂��擾
		std::vector<Field::FieldPosition> GetAround() const;

		//�p�X�v�Z
		void GetPath(std::deque<D3DXVECTOR3>& pathList) const;

		//�ύX
		void Change(const Field::Model::PlaceModel *place);

	private:
		const FieldPosition Position;		//�m�[�h���W
		
		AStarNode *parent;					//�e�m�[�h

		int realCost;						//���R�X�g
		int heuristicCost;					//�q���[���X�e�B�b�N�R�X�g

		std::vector<Field::Model::Adjacency> adjacencyList;	//�אڏ��
	};

	/**************************************
	AStar�Ǘ��N���X
	***************************************/
	class AStarController
	{
	public:
		//�R���X�g���N�^�A�f�X�g���N�^
		AStarController();
		~AStarController();

		//�v���C�X���؂�ւ�����ۂ̃m�[�h�ύX����
		void OnChangePlace(const Field::Model::PlaceModel* place);

		//�X�^�[�g����S�[���ւ̌v�Z����
		std::deque<D3DXVECTOR3> CalcRoute(const Field::FieldPosition& start, const Field::FieldPosition& goal, const Field::FieldPosition& town);

		static const unsigned MaxCheckRoute;

	private:
		//�m�[�h�}�b�v
		std::map<FieldPosition, std::unique_ptr<AStarNode>> nodeMap;

		//�I�[�v�����X�g
		std::list<AStarNode*> openList;

		//�N���[�Y���X�g
		std::list<AStarNode*> closeList;

		//�ŏ��X�R�A�̃m�[�h�擾
		AStarNode* SearchMinScoreNode(const Field::FieldPosition& goal);

		//�m�[�h�̎��͂̃}�X���I�[�v������
		void OpenAroundNode(AStarNode* node);

		//�m�[�h���N���[�Y����
		void CloseNode(AStarNode* node);
	};
}

#endif