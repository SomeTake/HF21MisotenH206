//=====================================
//
// �Q�[���^�C�g��[GameTitle.cpp]
// �@�\�F�^�Ct�����
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "GameTitle.h"

//=====================================
// ���ꏈ��
//=====================================
void GameScene::GameTitle::OnStart(GameScene & entity)
{
	//�X�R�A�\���A���O���͂ȂǂȂ�
}

//=====================================
// �X�V����
//=====================================
GameScene::State GameScene::GameTitle::OnUpdate(GameScene & entity)
{
	//���͂Ƃ肠�������������
	State next = State::Title;
	return next;
}
