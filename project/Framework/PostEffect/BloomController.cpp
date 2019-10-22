//=====================================
//
//�u���[���R���g���[������[BloomController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BloomController.h"
#include "../Tool/DebugWindow.h"

#define DEBGU_BLOOM
/**************************************
static�����o
***************************************/
const float BloomController::DefaultPower = 0.3f;
const float BloomController::DefaultThrethold = 0.4f;

/**************************************
�R���X�g���N�^
***************************************/
BloomController::BloomController() :
	bloomPower(),
	bloomThrethold()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�p���[�Ƃ������l�̏�����
	bloomPower[0] = bloomPower[1] = bloomPower[2] = DefaultPower;
	bloomThrethold[0] = bloomThrethold[1] = bloomThrethold[2] = DefaultThrethold;

	//�u���[���t�B���^�̃C���X�^���X�A�e�N�X�`���A�T�[�t�F�C�X��ݒ�
	bloomFilter = new BloomFilter(SCREEN_WIDTH, SCREEN_HEIGHT);

	//�u���[�t�B���^�̃C���X�^���X�A�e�N�X�`���A�T�[�t�F�C�X��ݒ�
	blurFilter = new BlurFilter();
	for (int i = 0; i < 3; i++)
	{
		int reduction = (int)powf(2.0f, i + 2.0f);
		for (int j = 0; j < 2; j++)
		{
			pDevice->CreateTexture(SCREEN_WIDTH / reduction, SCREEN_HEIGHT / reduction, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &blurTexture[i][j], 0);
			blurTexture[i][j]->GetSurfaceLevel(0, &blurSurface[i][j]);
		}

		//�u���[�t�B���^�p�̃r���[�|�[�g��ݒ�
		blurViewPort[i].Width = SCREEN_WIDTH / reduction;
		blurViewPort[i].Height = SCREEN_HEIGHT / reduction;
		blurViewPort[i].X = 0;
		blurViewPort[i].Y = 0;
		blurViewPort[i].MinZ = 0.0f;
		blurViewPort[i].MaxZ = 1.0f;
	}
}

/**************************************
�f�X�g���N�^
***************************************/
BloomController::~BloomController()
{
	delete blurFilter;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SAFE_RELEASE(blurTexture[j][i]);
			SAFE_RELEASE(blurSurface[j][i]);
		}
	}

	delete bloomFilter;
}

/**************************************
�`�揈��
***************************************/
void BloomController::Draw(LPDIRECT3DTEXTURE9 texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�u���[����������̂ŃT���v�����O��CLAMP�ɐݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//�r���[�|�[�g��ޔ�
	pDevice->GetViewport(&oldViewPort);

	//���݂̃����_�[�^�[�Q�b�g��ޔ�
	LPDIRECT3DSURFACE9 oldSurface;
	pDevice->GetRenderTarget(0, &oldSurface);

	//�P�x���o����
	SampleBrightness(texture);

	//���o�����P�x���u���[����
	ProcessBlur();

	//�����_�[�^�[�Q�b�g�����ɖ߂�
	pDevice->SetRenderTarget(0, oldSurface);
	SAFE_RELEASE(oldSurface);

	//�u���[������
	BlendBloom();

	//Z�o�b�t�@�ɏ������ނ悤�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//�T���v�����O�����Ƃɖ߂�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

#ifdef _DEBUG_BLOOM
	Debug::Begin("Bloom");
	for (int i = 0; i < 3; i++)
	{
		Debug::DrawTexture(blurTexture[i][0], { 200.0f, 100.0f });
		Debug::SameLine();
	}
	Debug::End();
#endif
}

/**************************************
�p���[�ݒ菈��
***************************************/
void BloomController::SetPower(float power1, float power2, float power3)
{
	bloomPower[0] = power1;
	bloomPower[1] = power2;
	bloomPower[2] = power3;
}

/**************************************
�������l�ݒ菈��
***************************************/
void BloomController::SetThrethold(float threthold1, float threthold2, float threthold3)
{
	bloomThrethold[0] = threthold1;
	bloomThrethold[1] = threthold2;
	bloomThrethold[2] = threthold3;
}

/**************************************
���x���o����
***************************************/
void BloomController::SampleBrightness(LPDIRECT3DTEXTURE9 targetTexture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < 3; i++)
	{
		//�����_�[�^�[�Q�b�g��ݒ肵�N���A
		pDevice->SetRenderTarget(0, blurSurface[i][0]);
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

		//�r���[�|�[�g��ݒ�
		pDevice->SetViewport(&blurViewPort[i]);

		//�u���[���̃p�����[�^��ݒ�
		bloomFilter->SetBloomPower(bloomPower[i]);
		bloomFilter->SetThrethold(bloomThrethold[i]);

		float reduction = powf(2.0f, i + 2.0f);
		bloomFilter->Resize(SCREEN_WIDTH / reduction, SCREEN_HEIGHT / reduction);

		pDevice->SetTexture(0, targetTexture);

		bloomFilter->DrawEffect(0);
	}
}

/**************************************
�u���[����
***************************************/
void BloomController::ProcessBlur()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const int PassMax = 2;
	const int TextureMax = 2;

	//�u���[�p�̃T�[�t�F�C�X���N���A
	for (int i = 0; i < 3; i++)
	{
		pDevice->SetRenderTarget(0, blurSurface[i][1]);
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);
	}

	for (int j = 0; j < 3; j++)
	{
		//�r���[�|�[�g��ݒ�
		pDevice->SetViewport(&blurViewPort[j]);

		float reduction = powf(2.0f, j + 2.0f);
		blurFilter->SetSurfaceSize(SCREEN_WIDTH / reduction, SCREEN_HEIGHT / reduction);

		cntBlur = 1;

		//�u���[����
		const int BlurLoop = 3;
		for (int i = 0; i < BlurLoop; i++, cntBlur++)
		{
			pDevice->SetRenderTarget(0, blurSurface[j][cntBlur % TextureMax]);
			pDevice->SetTexture(0, blurTexture[j][(cntBlur + 1) % TextureMax]);
			blurFilter->DrawEffect(cntBlur % PassMax);
		}
	}

	//�r���[�|�[�g�����Ƃɖ߂�
	pDevice->SetViewport(&oldViewPort);
}

/**************************************
�u���[����������
***************************************/
void BloomController::BlendBloom()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�|�[�g�����Ƃɖ߂�
	pDevice->SetViewport(&oldViewPort);

	//�����_�[�X�e�[�g�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	bloomFilter->Resize(SCREEN_WIDTH, SCREEN_HEIGHT);

	pDevice->SetTexture(0, blurTexture[0][cntBlur % 2]);
	pDevice->SetTexture(1, blurTexture[1][cntBlur % 2]);
	pDevice->SetTexture(2, blurTexture[2][cntBlur % 2]);

	bloomFilter->DrawEffect(1);

	//�����_�[�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}