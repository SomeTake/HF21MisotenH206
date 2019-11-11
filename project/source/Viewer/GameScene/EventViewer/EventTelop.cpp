//=============================================================================
//
// �C�x���g�e���b�v���� [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "EventTelop.h"

#ifdef _DEBUG

#include "../../../../Framework/Input/input.h"

#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�A�j���[�V�����̐�
static const int animMax = 5;

//�e�L�X�g�A�j���[�V�����J�n�ʒu
static const float textStartPositionX[animMax] = {
	SCREEN_WIDTH*1.5,
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5
};

//�e�L�X�g�A�j���[�V�����I���ʒu
static const float textEndPositionX[animMax] = {
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5,
	-SCREEN_WIDTH * 1.5
};

//�e�L�X�g�A�j���[�V�������
static const EaseType animType[animMax] = {
	OutCirc,
	OutCirc,
	InOutCubic,
	InCirc,
	OutCirc
};

//�e�L�X�g�A�j���[�V�����Ԋu(������ύX����ƃA�j���[�V�����̑����𒲐��ł���)
//*����(0������Ɩ�����ɂȂ邩��A�j���[�V�������̂��̂��폜���邱��)
static const float animDuration[animMax] = {
	15,
	50,
	5,
	30,
	15
};

//�A�j���[�V�����V�[��
enum TelopAnimScene
{
	BG_Open,
	Text_In,
	Text_Stop,
	Text_Out,
	BG_Close
};

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventTelop::EventTelop() :
	currentAnim(0)
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventTelop/Text/Text.png");
	text->size = D3DXVECTOR3(1024, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_WIDTH*1.5, SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	text->MakeVertex();

	//�w�i
	bg = new BaseViewerDrawer();
	bg->LoadTexture("data/TEXTURE/Viewer/EventViewer/EventTelop/BG/BG.png");
	bg->size = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->MakeVertex();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventTelop::~EventTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(bg);
}

//=============================================================================
// �X�V����
//=============================================================================
void EventTelop::Update()
{
	//�e���b�v�Đ�����
	Play();
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventTelop::Draw(void)
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	//�w�i���ɕ`��
	bg->Draw();

	//�e�L�X�g
	text->Draw();
}

//=============================================================================
// �e���b�v�Đ�����
//=============================================================================
void EventTelop::Play()
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	//�t���[���X�V
	countFrame++;

	//���ԍX�V
	animTime = countFrame / animDuration[currentAnim];

	//�A�j���[�V�����V�[����BG_Open�̊Ԕw�i���I�[�v������
	if (currentAnim == BG_Open)
	{
		OpenBG();
	}

	//�|�W�V�������X�V
	text->position.x = Easing::EaseValue(animTime,
		textStartPositionX[currentAnim],
		textEndPositionX[currentAnim],
		animType[currentAnim]);

	//�A�j���[�V�����V�[����BG_Close�̊Ԕw�i���N���[�Y����
	if (currentAnim == BG_Close)
	{
		CloseBG();
	}

	//�A�j���[�V�����X�V
	if (countFrame == animDuration[currentAnim])
	{
		countFrame = 0;
		currentAnim++;
	}

	//�A�j���[�V�����I��
	if (currentAnim >= animMax)
	{
		countFrame = 0;
		currentAnim = 0;
		isPlaying = false;

		//�k���`�F�b�N
		if (Callback != nullptr)
		{
			//�Đ��I���̒ʒm
			Callback();
		}
	}
}

//=============================================================================
// �w�i���J������
//=============================================================================
void EventTelop::OpenBG(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float bgEasingStart = 0.0f;
	float bgEasingGoal = 128.0f;

	//�w�i��Y�T�C�Y���X�V
	bg->size.y = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Open]);

	//bg->size.y�̍ő��bgEasingGoal�ɐݒ�
	Math::WrapAround(bg->size.y, bgEasingGoal, bg->size.y);
}

//=============================================================================
// �w�i����鏈��
//=============================================================================
void EventTelop::CloseBG(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float bgEasingStart = 128.0f;
	float bgEasingGoal = 0.0f;

	//�w�i��Y�T�C�Y���X�V
	bg->size.y = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Close]);

	//bg->size.y�̍ŏ���bgEasingGoal�ɐݒ�
	Math::WrapAround(bg->size.y, bgEasingGoal, bg->size.y);
}

//=============================================================================
// �e�N�X�`�����󂯓n������
//=============================================================================
void EventTelop::PassTexture(TelopID id)
{
	//�e�L�X�g��UV��ύX
	text->SetTexture(1, Max, id);

	bool isNegative;

	if (id >= Meteorite)
	{
		isNegative = true;
	}
	else
	{
		isNegative = false;
	}

	//�w�i��UV��ύX
	bg->SetTexture(1, 2, isNegative);
	bg->vertexWk[1].tex.x = 3.0f;
	bg->vertexWk[3].tex.x = 3.0f;
}

//=============================================================================
// �e���b�v�Z�b�g����
//=============================================================================
void EventTelop::Set(TelopID id, std::function<void(void)> Callback)
{
	//�e�N�X�`�����󂯓n��
	PassTexture(id);

	//�Đ���Ԃɂ���
	isPlaying = true;

	//�e���b�v�Đ��I���ʒm
	this->Callback = Callback;
}
