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

//�e���b�v�̎�ސ�
const int EventTelop::typeMax;

//�e�L�X�g�̃e�N�X�`���p�X
static const char *textTexPath[EventTelop::typeMax]
{
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/PositiveText01.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/PositiveText02.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/NegativeText01.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/Text/NegativeText02.png",
};

//�w�i�̃e�N�X�`���p�X
static const char *bgTexPath[EventTelop::typeMax]
{
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/PositiveBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/PositiveBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/NegativeBG.png",
	"data/TEXTURE/Viewer/EventViewer/EventTelop/BG/NegativeBG.png",
};

//�A�j���[�V�����̐�
static const int animMax = 5;

//�e�L�X�g�A�j���[�V�����J�n�ʒu
static const float textStartPositionX[animMax] = {
	SCREEN_WIDTH*1.2,
	SCREEN_WIDTH*1.2,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.2
};

//�e�L�X�g�A�j���[�V�����I���ʒu
static const float textEndPositionX[animMax] = {
	SCREEN_WIDTH*1.2,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.2,
	-SCREEN_WIDTH * 1.2
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
EventTelop::EventTelop()
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->size = D3DXVECTOR3(512, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_WIDTH*1.2, SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	text->SetColor(SET_COLOR_NOT_COLORED);
	text->MakeVertex();

	//�w�i
	bg = new BaseViewerDrawer();
	bg->size = D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);
	bg->MakeVertex();

	//�w�i��UV���W��ύX
	bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bg->vertexWk[1].tex = D3DXVECTOR2(3.0, 0.0f);
	bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bg->vertexWk[3].tex = D3DXVECTOR2(3.0f, 1.0f);

	//�R���e�i�Ƀe�N�X�`���������[�h����
	for (int i = 0; i < typeMax; i++)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		LPDIRECT3DTEXTURE9 tTex;
		LPDIRECT3DTEXTURE9 bgTex;

		D3DXCreateTextureFromFile(pDevice,
			textTexPath[i],
			&tTex);

		textTexContainer.push_back(tTex);

		D3DXCreateTextureFromFile(pDevice,
			bgTexPath[i],
			&bgTex);

		bgTexContainer.push_back(bgTex);
	}
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
	bg->SetVertex();

	//�e�L�X�g
	text->Draw();
	text->SetVertex();
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
	float bgEasingGoal = 60.0f;

	//�w�i�A�N�e�B�u�p�[�Z���e�[�W���X�V
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
	float bgEasingStart = 60.0f;
	float bgEasingGoal = 0.0f;

	//�w�i�A�N�e�B�u�p�[�Z���e�[�W���X�V
	bg->size.y = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Close]);

	//bg->size.y�̍ŏ���bgEasingGoal�ɐݒ�
	Math::WrapAround(bg->size.y, bgEasingGoal, bg->size.y);
}

//=============================================================================
// �e�N�X�`�����󂯓n������
//=============================================================================
void EventTelop::PassTexture(TelopID id)
{
	text->texture = textTexContainer[id];
	bg->texture = bgTexContainer[id];
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
