//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"

namespace Input
{
	//*****************************************************************************
	// �O���[�o���ϐ�
	//*****************************************************************************
	LPDIRECTINPUT8 pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^

	//=============================================================================
	// ���͏����̏�����
	//=============================================================================
	HRESULT Init(HINSTANCE hInst, HWND hWnd)
	{
		HRESULT hr;

		if(!pDInput)
		{
			// DirectInput�I�u�W�F�N�g�̍쐬
			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
				IID_IDirectInput8, (void**)&pDInput, NULL);
		}

		// �L�[�{�[�h�̏�����
		Keyboard::Init(hInst, hWnd, pDInput);

		//�}�E�X������
		Mouse::Init(hInst, hWnd, pDInput);

		//�p�b�h����������
		GamePad::Init(pDInput);

		return S_OK;
	}

	//=============================================================================
	// ���͏����̏I������
	//=============================================================================
	void Uninit()
	{
		// �L�[�{�[�h�̏I������
		Keyboard::Uninit();

		//�}�E�X�I������
		Mouse::Uninit();

		//�p�b�h�I������
		GamePad::Uninit();

		if (pDInput)
		{// DirectInput�I�u�W�F�N�g�̊J��
			pDInput->Release();
			pDInput = NULL;
		}
	}

	//=============================================================================
	// ���͏����̍X�V����
	//=============================================================================
	void Update(void)
	{
		// �L�[�{�[�h�̍X�V
		Keyboard::Update();

		//�}�E�X�X�V����
		Mouse::Update();

		//�Q�[���p�b�h�X�V����
		GamePad::Update();
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetPressHorizontail(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetPress(DIK_LEFT) || GamePad::GetPress(0, BUTTON_LEFT))
				return -1.0f;

			if (Keyboard::GetPress(DIK_RIGHT) || GamePad::GetPress(0, BUTTON_RIGHT))
				return 1.0f;

			return 0.0f;
		}

		if (GamePad::GetPress(no, BUTTON_LEFT))
			return -1.0f;

		if (GamePad::GetPress(no, BUTTON_RIGHT))
			return 1.0f;

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetPressVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetPress(DIK_DOWN) || GamePad::GetPress(0, BUTTON_DOWN))
				return -1.0f;

			if (Keyboard::GetPress(DIK_UP) || GamePad::GetPress(0, BUTTON_UP))
				return 1.0f;

			return 0.0f;
		}

		if (GamePad::GetPress(no, BUTTON_DOWN))
			return -1.0f;

		if (GamePad::GetPress(no, BUTTON_UP))
			return 1.0f;

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetRepeatHorizontal(int no)
	{
		//TODO:�Q�[���p�b�h�����s�[�g���͂ɑΉ�
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_LEFT))
				return -1.0f;

			if (Keyboard::GetRepeat(DIK_RIGHT))
				return 1.0f;

			return 0.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetRepeatVertical(int no)
	{
		//TODO:�Q�[���p�b�h�����s�[�g���͂ɑΉ�
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_DOWN))
				return -1.0f;

			if (Keyboard::GetRepeat(DIK_UP))
				return 1.0f;

			return 0.0f;
		}

		return 0.0f;
	}
}