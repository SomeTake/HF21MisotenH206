//=====================================
//
// �Q�[�����U���g[GameResult.cpp]
// �@�\�F���U���g���
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GameResult.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	//�X�R�A�\���A���O���͂ȂǂȂ�
}

//=====================================
// �X�V����
//=====================================
GameScene::State GameScene::GameResult::OnUpdate(GameScene & entity)
{
	//���͂Ƃ肠�������������
	State next = State::Result;
	return next;
}
