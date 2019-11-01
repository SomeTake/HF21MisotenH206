//=====================================
//
//AStarController.cpp
//�@�\:A*�A���S���Y���̃R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "AStarController.h"
#include "../Place/FieldPlaceModel.h"

namespace Field::Route
{
	/**************************************
	static�����o
	***************************************/
	const unsigned AStarController::MaxCheckRoute = 10000;

	/**************************************
	AStarNode�R���X�g���N�^
	***************************************/
	AStarNode::AStarNode(const Field::Model::PlaceModel * place) :
		Position(place->GetPosition()),
		parent(nullptr),
		realCost(9999),
		heuristicCost(9999)
	{
		adjacencyList.reserve(Field::Model::Adjacency::Max);
		adjacencyList = place->GetConnectingAdjacency();
	}

	/**************************************
	AStarNode�f�X�g���N�^
	***************************************/
	AStarNode::~AStarNode()
	{
	}

	/**************************************
	AStarNode�X�R�A�擾����
	***************************************/
	int AStarNode::GetScore() const
	{
		return realCost + heuristicCost;
	}

	/**************************************
	AStarNode ���R�X�g�擾����
	***************************************/
	int AStarNode::GetCost() const
	{
		return realCost;
	}

	/**************************************
	AStarNode�q���[���X�e�B�b�N�R�X�g�v�Z����
	***************************************/
	void AStarNode::CalcHeuristicCost(const Field::FieldPosition & goal)
	{
		heuristicCost = (int)fabsf((float)goal.x - Position.x) + (int)fabsf((float)goal.z - Position.z);
	}

	/**************************************
	AStarNode Open����
	***************************************/
	void AStarNode::Open(AStarNode * parent, int realCost)
	{
		this->parent = parent;
		this->realCost = realCost;
	}

	/**************************************
	AStarNode ���͂̍s����}�X�̍��W���擾
	***************************************/
	std::vector<Field::FieldPosition> AStarNode::GetAround() const
	{
		using Field::Model::Adjacency;

		std::vector<FieldPosition> out;
		out.reserve(4);

		if (Utility::IsContain(adjacencyList, Adjacency::Back))
			out.push_back(Position + FieldPosition(0, -1));
		if (Utility::IsContain(adjacencyList, Adjacency::Forward))
			out.push_back(Position + FieldPosition(0, 1));
		if (Utility::IsContain(adjacencyList, Adjacency::Right))
			out.push_back(Position + FieldPosition(1, 0));
		if (Utility::IsContain(adjacencyList, Adjacency::Left))
			out.push_back(Position + FieldPosition(-1, 0));

		return out;
	}

	/**************************************
	AStarNode �p�X�擾
	***************************************/
	void AStarNode::GetPath(std::deque<D3DXVECTOR3>& pathList) const
	{
		pathList.push_front(Position.ConvertToWorldPosition());

		if (parent != nullptr)
			parent->GetPath(pathList);
	}

	/**************************************
	AStarNode �ύX����
	***************************************/
	void AStarNode::Change(const Field::Model::PlaceModel * place)
	{
		//�אڏ����X�V����
		adjacencyList = place->GetConnectingAdjacency();
	}

	/**************************************
	AStarController�R���X�g���N�^
	***************************************/
	AStarController::AStarController()
	{
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	AStarController::~AStarController()
	{
		nodeMap.clear();
	}

	/**************************************
	�m�[�h�ύX����
	***************************************/
	void AStarController::OnChangePlace(const Field::Model::PlaceModel * place)
	{
		Field::FieldPosition key = place->GetPosition();

		if (nodeMap.count(key) == 0)
		{
			AStarNode *node = new AStarNode(place);
			nodeMap.emplace(key, std::unique_ptr<AStarNode>(node));
		}
		else
		{
			nodeMap[key]->Change(place);
		}
	}

	/**************************************
	���[�g�v�Z����
	***************************************/
	std::deque<D3DXVECTOR3> AStarController::CalcRoute(const Field::FieldPosition &start, const Field::FieldPosition &goal)
	{
		closeList.clear();
		openList.clear();

		//�S�[���n�_�̃m�[�h���擾
		AStarNode *goalNode = nodeMap[goal].get();

		//�X�^�[�g�n�_�̃m�[�h���擾���ăI�[�v��
		AStarNode *node = nodeMap[start].get();
		node->Open(nullptr, 0);
		openList.push_back(node);

		//�ڕW�ւ̃��[�g
		std::deque<D3DXVECTOR3> route;

		//���s�񐔂𐔂��āA2000�񒴂����狭�����f
		for (int i = 0; i < 10000; ++i)
		{
			//�I�[�v�������m�[�h���N���[�Y����
			CloseNode(node);

			//�m�[�h�̎��͂��I�[�v������
			OpenAroundNode(node);

			//�ŏ��X�R�A�̃m�[�h������
			node = SearchMinScoreNode(goal);

			//�܏��H
			if (node == nullptr)
			{
				break;
			}
			//�S�[���ɓ���
			else if (node == goalNode)
			{
				CloseNode(node);
				node->GetPath(route);
				break;
			}
		}

		return route;
	}

	/**************************************
	�ŏ��X�R�A�̃m�[�h����
	***************************************/
	AStarNode * AStarController::SearchMinScoreNode(const Field::FieldPosition& goal)
	{
		//�ŏ��X�R�A
		int minScore = 99999;
		
		//�ŏ����R�X�g
		int minCost = 99999;

		AStarNode *minNode = nullptr;
		for (auto&& node : openList)
		{
			int score = node->GetScore();

			if (score > minScore)
			{
				continue;
			}
			if (score == minScore && node->GetCost() >= minCost)
			{
				continue;
			}

			//�X�V
			minScore = score;
			minCost = node->GetCost();
			minNode = node;
		}

		return minNode;
	}

	/**************************************
	���͂̃m�[�h���I�[�v������
	***************************************/
	void AStarController::OpenAroundNode(AStarNode * node)
	{
		using Field::FieldPosition;

		//�q�����Ă���������擾
		std::vector<FieldPosition> adjacencies = node->GetAround();

		//�I�[�v��
		for (auto&& adjacency : adjacencies)
		{
			AStarNode *around = nodeMap[adjacency].get();

			if (Utility::IsContain(closeList, around))
			{
				continue;
			}

			around->Open(node, node->GetCost() + 1);
			openList.push_back(around);
		}
	}

	/**************************************
	�m�[�h���N���[�Y����
	***************************************/
	void AStarController::CloseNode(AStarNode * node)
	{
		openList.remove(node);
		closeList.push_back(node);
	}

}