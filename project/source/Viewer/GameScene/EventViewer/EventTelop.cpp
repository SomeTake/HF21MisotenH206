//=============================================================================
//
// �C�x���g�e���b�v���� [EventTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
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
//*����(0������Ɩ����ɂȂ邩��A�j���[�V�������̂��̂��폜���邱��)
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
	InText,
	StopText,
	OutText,
	BG_Close
};

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventTelop::EventTelop()
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->MakeVertex();
	text->size = D3DXVECTOR3(512, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_WIDTH*1.2, SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	text->SetColor(SET_COLOR_NOT_COLORED);

	//�w�i
	bg = new BaseViewerDrawer();
	MakeVertexBG();
	bg->size = D3DXVECTOR3(SCREEN_WIDTH / 2, 60.0f, 0.0f);
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->position = D3DXVECTOR3((float)(SCREEN_WIDTH / 10 * 5), SCREEN_HEIGHT / 10 * 5.0f, 0.0f);
	bg->SetColor(SET_COLOR_NOT_COLORED);

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
	Play();

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_T))
	{
		Set(PositiveEvent01, nullptr);
	}

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventTelop::Draw(void)
{
	//�Đ����Ȃ�`��
	if (isPlaying)
	{
		//�w�i���ɕ`��
		bg->Draw();
		SetVertexBG(percentageBG);

		text->Draw();
		text->SetVertex();
	}
}

//=============================================================================
// �e���b�v�Đ�����
//=============================================================================
void EventTelop::Play()
{
	if (isPlaying)
	{
		//�t���[���X�V
		countFrame++;

		//���ԍX�V
		animTime = countFrame / animDuration[currentAnim];

		//�A�j���[�V������WaitBG_Open�̊Ԕw�i���I�[�v������
		if (currentAnim == BG_Open)
		{
			OpenBG();
		}

		//�|�W�V�������X�V
		text->position.x = Easing::EaseValue(animTime,
			textStartPositionX[currentAnim],
			textEndPositionX[currentAnim],
			animType[currentAnim]);

		//�A�j���[�V������WaitBG_Close�̊Ԕw�i���N���[�Y����
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
}

//=============================================================================
// �w�i�e�N�X�`���̒��_�̍쐬
//=============================================================================
void EventTelop::MakeVertexBG()
{
	//�ŏ��̓A�N�e�B�u�p�[�Z���e�[�W��0�ɐݒ�
	percentageBG = 0.0f;

	// ���_���W�̐ݒ�
	bg->vertexWk[0].vtx = D3DXVECTOR3(0, bg->position.y - bg->size.y*percentageBG, bg->position.z);
	bg->vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, bg->position.y - bg->size.y*percentageBG, bg->position.z);
	bg->vertexWk[2].vtx = D3DXVECTOR3(0, bg->position.y + bg->size.y*percentageBG, bg->position.z);
	bg->vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, bg->position.y + bg->size.y*percentageBG, bg->position.z);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	bg->vertexWk[0].rhw =
		bg->vertexWk[1].rhw =
		bg->vertexWk[2].rhw =
		bg->vertexWk[3].rhw = 1.0f;

	// �e�N�X�`�����W�̐ݒ�
	bg->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	bg->vertexWk[1].tex = D3DXVECTOR2(3.0, 0.0f);
	bg->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	bg->vertexWk[3].tex = D3DXVECTOR2(3.0f, 1.0f);
}

//=============================================================================
// �w�i�̒��_���W�̐ݒ�
//=============================================================================
void EventTelop::SetVertexBG(float percentageBG)
{
	// ���_���W�̐ݒ�
	bg->vertexWk[0].vtx = D3DXVECTOR3(0, bg->position.y - bg->size.y*percentageBG, bg->position.z);
	bg->vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, bg->position.y - bg->size.y*percentageBG, bg->position.z);
	bg->vertexWk[2].vtx = D3DXVECTOR3(0, bg->position.y + bg->size.y*percentageBG, bg->position.z);
	bg->vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, bg->position.y + bg->size.y*percentageBG, bg->position.z);
}

//=============================================================================
// �w�i���J������
//=============================================================================
void EventTelop::OpenBG(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float bgEasingStart = 0.0f;
	float bgEasingGoal = 1.0f;

	//�w�i�A�N�e�B�u�p�[�Z���e�[�W���X�V
	percentageBG = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Open]);

	if (percentageBG >= bgEasingGoal)
	{
		percentageBG = 1.0f;
	}
}

//=============================================================================
// �w�i����鏈��
//=============================================================================
void EventTelop::CloseBG(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float bgEasingStart = 1.0f;
	float bgEasingGoal = 0.0f;

	//�w�i�A�N�e�B�u�p�[�Z���e�[�W���X�V
	percentageBG = Easing::EaseValue(animTime, bgEasingStart, bgEasingGoal, animType[BG_Close]);

	if (percentageBG <= bgEasingGoal)
	{
		percentageBG = 0.0f;
	}
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
