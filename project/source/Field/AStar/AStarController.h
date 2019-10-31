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

#include <vector>
#include <map>

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
	�m�[�h�̍��W�\����
	***************************************/
	struct NodePosition
	{
		float x, z;

		//�R���X�g���N�^
		NodePosition(const D3DXVECTOR3& position);

		//+���Z�q
		NodePosition operator+(const NodePosition& rhs);

		//<���Z�q
		bool operator < (const NodePosition& rhs);

		//���[���h���W�ւ̕ϊ�
		D3DXVECTOR3 ToWorld();
	};

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

		//�q���[���X�e�B�b�N�R�X�g�v�Z
		void CalcHeuristicCost(const NodePosition& goal);

		//�I�[�v������
		void Open(AStarNode *parent, int realCost);

		//�ړ��\�Ȕ͈͂��擾
		std::vector<NodePosition> GetAround() const;

		//�p�X�v�Z
		void GetPath(std::vector<const D3DXVECTOR3>& pathList) const;

	private:
		const NodePosition Position;		//�m�[�h���W
		
		AStarNode *parent;					//�e�m�[�h

		int realScore;						//���R�X�g
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
		std::vector<const D3DXVECTOR3> CalcRoute(const D3DXVECTOR3& start, const D3DXVECTOR3& goal);

	private:
		//�m�[�h�}�b�v
		std::map<NodePosition, std::unique_ptr<AStarNode>> nodeMap;

		//�I�[�v�����X�g
		std::vector<const AStarNode*> openList;

		//�N���[�Y���X�g
		std::vector<const AStarNode*> closeList;
	};
}

#endif