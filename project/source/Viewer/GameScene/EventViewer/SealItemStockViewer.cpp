//=============================================================================
//
// �X�g�b�N����r���A�[���� [SealItemStockViewer.cpp]
// Author : Yu Oohama (bnSeal987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "SealItemStockViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"
#include "../../../../Framework/Math/Easing.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#endif

//*****************************************************************************
// *���ӁF����A�j���[�V�����ƕ�������A�j���[�V�����͎d�l�����܂��ĂȂ����߁A
// �b��I�ɃT�C�Y�_�E���A�t�F�[�h�A�E�g�����s�B
//*****************************************************************************

//�A�C�R���̏����T�C�Y
const D3DXVECTOR2 initIconSize = D3DXVECTOR2(400.0f, 400.0f);
const float ScaleNum = 0.5f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
SealItemStockViewer::SealItemStockViewer()
{
	//�A�C�R��
	Icon = new TextureDrawer(D3DXVECTOR2(800.0f, 400.0f), 2, 1);
	Icon->LoadTexture("data/TEXTURE/Viewer/EventViewer/SealItemStockViewer/SealIcon.png");
	Icon->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.47f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f));
	Icon->SetIndex(0);

	//�A�C�R��(��)
	Icon_White = new TextureDrawer(D3DXVECTOR2(800.0f, 400.0f), 2, 1, false);
	Icon_White->LoadTexture("data/TEXTURE/Viewer/EventViewer/SealItemStockViewer/SealIcon.png");
	Icon_White->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.47f, SCREEN_HEIGHT / 10 * 3.5f, 0.0f));
	Icon_White->SetIndex(1);
	Icon_White->SetSize(initIconSize * ScaleNum);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
SealItemStockViewer::~SealItemStockViewer()
{
	SAFE_DELETE(Icon);
	SAFE_DELETE(Icon_White);
}

//=============================================================================
// �X�V����
//=============================================================================
void SealItemStockViewer::Update(void)
{
	if (!isPlaying)
		return;

	if (!GetInPause())
	{
		Icon_White->Update();
		Icon->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void SealItemStockViewer::Draw(void)
{
	//�v���C���Ȃ�`��
	if (!isPlaying)
		return;

	if (!GetInPause())
	{
		Icon_White->Draw();
		Icon->Draw();
	}
}


//=============================================================================
// ����̃J�E���g�_�E�����J�n
//=============================================================================
void SealItemStockViewer::CountDownStart(void)
{
	Icon_White->Expand(285.0f, ExpandType::ExpandUpToDown);
	Icon->Close(285.0f, CloseType::CloseUpToDown, EaseType::Linear, [&]()
	{
		isPlaying = false;
	});
}

//=============================================================================
// �X�g�b�N����A�C�R����ݒu����
//=============================================================================
void SealItemStockViewer::SetBanIcon(std::function<bool(void)> func)
{
	// ������
	GetInPause = func;
	isPlaying = true;
	Icon->Reset();
	Icon->SetSize(initIconSize);
	Icon->SetVisible(true);
	Icon_White->Reset();
	Icon_White->SetVisible(false);

	Icon->SetScale(15.0f, 0.5f, EaseType::Linear, [&]()
	{
		CountDownStart();
	});
}

//=============================================================================
// �r���A�[�̃��Z�b�g
//=============================================================================
void SealItemStockViewer::Reset(void)
{
	isPlaying = false;
	Icon->SetSize(initIconSize);
	Icon->SetVisible(false);
	Icon_White->SetVisible(false);
}
