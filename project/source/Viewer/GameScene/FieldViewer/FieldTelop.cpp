//=============================================================================
//
// �t�B�[���h�e���b�v���� [FieldTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "FieldTelop.h"

#ifdef _DEBUG

#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"

#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�e�L�X�g�̃e�N�X�`���p�X
static const char *textTexPath[FieldTelop::Max]
{
	"data/TEXTURE/Viewer/FieldViewer/FieldTelop/TextCity.png",
};

//�A�j���[�V�����̐�
static const int animMax = 4;

//�e�L�X�g�A�j���[�V�����J�n�ʒu
static const float textStartPositionY[animMax] = {
	SCREEN_CENTER_Y/1.5,
	SCREEN_CENTER_Y/1.5,
	SCREEN_CENTER_Y/2.7,
	SCREEN_CENTER_Y/2.7
};

//�e�L�X�g�A�j���[�V�����I���ʒu
static const float textEndPositionY[animMax] = {
	SCREEN_CENTER_Y/1.5,
	SCREEN_CENTER_Y/2.7,
	SCREEN_CENTER_Y/2.7,
	SCREEN_CENTER_Y/2.7 
};

//�e�L�X�g�A�j���[�V�������
static const EaseType animType[animMax] = {
	OutCirc,
	OutCirc,
	InOutCubic,
	InOutCubic
};

//�e�L�X�g�A�j���[�V�����Ԋu(������ύX����ƃA�j���[�V�����̑����𒲐��ł���)
//*����(0������Ɩ�����ɂȂ邩��A�j���[�V�������̂��̂��폜���邱��)
static const float animDuration[animMax] = {
	30,
	90,
	20,
	100
};

//�A�j���[�V�����V�[��
enum TelopAnimScene
{
	Line_Draw,
	Text_Raise,
	Wait,
	Telop_FadeOut,
};

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
FieldTelop::FieldTelop()
{
	//�e�L�X�g
	text = new BaseViewerDrawer();
	text->size = D3DXVECTOR3(512, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y/1.5, 0.0f);
	text->MakeVertex();

	//���C��
	line = new BaseViewerDrawer();
	line->LoadTexture("data/TEXTURE/Viewer/FieldViewer/FieldTelop/Line.png");
	line->size = D3DXVECTOR3(0.0f, 32.0f, 0.0f);
	line->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	line->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y/2, 0.0f);
	line->MakeVertex();

	//�R���e�i�Ƀe�N�X�`���������[�h����
	for (int i = 0; i < Max; i++)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		LPDIRECT3DTEXTURE9 tTex;

		D3DXCreateTextureFromFile(pDevice,
			textTexPath[i],
			&tTex);

		textTexContainer.push_back(tTex);
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
FieldTelop::~FieldTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(line);
}

//=============================================================================
// �X�V����
//=============================================================================
void FieldTelop::Update()
{
	//�e���b�v�Đ�����
	Play();

#ifdef _DEBUG

	Debug::Text("currentAnim:%d", currentAnim);
	Debug::Text("���l:%d", alpha);

#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void FieldTelop::Draw(void)
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	//�w�i���ɕ`��
	line->Draw();

	//�e�L�X�g
	DrawTelopText();
}

//=============================================================================
// �e���b�v�Đ�����
//=============================================================================
void FieldTelop::Play()
{
	//�Đ����Ȃ�`��
	if (!isPlaying) return;

	//�t���[���X�V
	countFrame++;

	//���ԍX�V
	animTime = countFrame / animDuration[currentAnim];

	//�A�j���[�V�����V�[����Line_Draw�̊Ԑ�������
	if (currentAnim == Line_Draw)
	{
		DrawLine();
	}

	//�A�j���[�V�����V�[����Telop_FadeOut�̊ԃt�F�[�h�A�E�g�����s
	if (currentAnim == Telop_FadeOut)
	{
		FadeOut();
	}

	//�|�W�V�������X�V
	text->position.y = Easing::EaseValue(animTime,
		textStartPositionY[currentAnim],
		textEndPositionY[currentAnim],
		animType[currentAnim]);

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
		alpha = 1.0f;
		text->SetAlpha(alpha);
		line->SetAlpha(alpha);
		line->size.x = 0.0f;
		text->position.y = textStartPositionY[0];
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
// ���C������������
//=============================================================================
void FieldTelop::DrawLine(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float lineEasingStart = 0.0f;
	float lineEasingGoal = 512.0f;

	//����X�T�C�Y���X�V
	line->size.x = Easing::EaseValue(animTime, lineEasingStart, lineEasingGoal, animType[Line_Draw]);

	//line->size.x�̍ő��lineEasingGoal�ɐݒ�
	Math::WrapAround(line->size.x, lineEasingGoal, line->size.x);
}

//=============================================================================
// �t�F�[�h�A�E�g����
//=============================================================================
void FieldTelop::FadeOut(void)
{
	//�C�[�W���O�̃X�^�[�g�ƃS�[����ݒ�
	float alphaEasingStart = 1.0f;
	float alphaEasingGoal = 0.0f;

	//���l���X�V
	alpha = Easing::EaseValue(animTime, alphaEasingStart, alphaEasingGoal, animType[Telop_FadeOut]);

	//alpha->size.x�̍ő��alphaEasingGoal�ɐݒ�
	Math::WrapAround(alpha, alphaEasingGoal, alpha);

	text->SetAlpha(alpha);
	line->SetAlpha(alpha);
}

//=============================================================================
// �e�L�X�g�`�揈��
//=============================================================================
void FieldTelop::DrawTelopText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	float percant;
	float t;
	float y;

	t = line->position.y - textEndPositionY[Text_Raise];

	//�e�L�X�g�̍��W�����C���̍��W��荂���ʒu�ɂ���������`��J�n
	if (text->position.y <= line->position.y)
	{
		y = text->position.y - textEndPositionY[Text_Raise];
		percant = 1.0f - (y / t);
	}
	else
	{
		percant = 0.0f;
	}

	// �e�N�X�`�����W�̐ݒ�
	text->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	text->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	text->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f*percant);
	text->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f*percant);

	// ���_���W�̐ݒ�
	text->vertexWk[0].vtx = text->position + D3DXVECTOR3(-text->size.x / 2, -text->size.y / 2, 0.0f);
	text->vertexWk[1].vtx = text->position + D3DXVECTOR3(text->size.x / 2, -text->size.y / 2, 0.0f);
	text->vertexWk[2].vtx = text->position + D3DXVECTOR3(-text->size.x / 2, text->size.y / 2*percant, 0.0f);
	text->vertexWk[3].vtx = text->position + D3DXVECTOR3(text->size.x / 2, text->size.y / 2*percant, 0.0f);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, text->texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, text->vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �e�N�X�`�����󂯓n������
//=============================================================================
void FieldTelop::PassTexture(TelopID id)
{
	text->texture = textTexContainer[id];
}

//=============================================================================
// �e���b�v�Z�b�g����
//=============================================================================
void FieldTelop::Set(TelopID id, std::function<void(void)> Callback)
{
	//�e�N�X�`�����󂯓n��
	PassTexture(id);

	//�Đ���Ԃɂ���
	isPlaying = true;

	//�e���b�v�Đ��I���ʒm
	this->Callback = Callback;
}
