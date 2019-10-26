//=============================================================================
//
// �C�x���g�r���A�[�Ǘ����� [EventViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include <vector>
#include "EventMessage.h"
#include "EventTelop.h"
#include "EventViewer.h"

#ifdef _DEBUG

#include "../../../../Framework/Tool/DebugWindow.h"
#include "../../../../Framework/Input/input.h"

#endif

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
EventViewer::EventViewer()
{
	eventViewer.push_back(eventTelop = new EventTelop());

	for (int i = 0; i < messageMax; i++)
	{
		eventViewer.push_back(eventMessage[i] = new EventMessage());
	}

	eventViewerMax = eventViewer.size();
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventViewer::~EventViewer()
{
	//�C���X�^���X����ꂽ�z����N���A
	eventViewer.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void EventViewer::Update()
{
	for (int i = 0; i < eventViewerMax; i++)
	{
		eventViewer[i]->Update();

	}

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_M))
	{
		SetEventMessage("�C�x���g�����I");
	}

	Debug::Begin("EventViewer");
	Debug::Text("MessageSetCnt:%d", messageSetCnt);
	Debug::End();

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void EventViewer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (int i = 0; i < eventViewerMax; i++)
	{
		eventViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// ���b�Z�[�W���J�E���g
//=============================================================================
void EventViewer::CountMessage(void)
{
	//�Z�b�g�J�E���g���J�E���g�A�b�v
	messageSetCnt++;

	if (messageSetCnt != 1)
	{
		//�ЂƂO�̃��b�Z�[�W���Đ��I�����Ă��Ȃ�J�E���g���Z�b�g
		if (!eventMessage[messageSetCnt - 2]->isPlaying)
		{
			messageSetCnt = 1;
		}
	}

	if (messageSetCnt > messageMax)
	{
		messageSetCnt = 1;
	}
}

//=============================================================================
// �C�x���g�������b�Z�[�W��ݒu(*������)
//=============================================================================
void EventViewer::SetEventMessage(const std::string Message)
{
	// �C�x���g���b�Z�[�W���Ȃ�
	if (Message.empty())
	{
		return;
	}

	CountMessage();
	eventMessage[messageSetCnt - 1]->SetEventMessage(Message, messageSetCnt);
}

//=============================================================================
// �C�x���g�����e���b�v��ݒu
//=============================================================================
void EventViewer::SetEventTelop(TelopID id, std::function<void(void)> Callback)
{
	eventTelop->Set(id, Callback);
}
