//=============================================================================
//
// �C�x���g�r���A�[�Ǘ����� [EventViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "../../../../Framework/Math/TMath.h"
#include "../EventViewer/EventMessage.h"
#include "../EventViewer/EventTelop.h"
#include "../EventViewer/SealItemStockViewer.h"
#include "../ParameterContainer/EventViewerParam.h"
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
	for (int i = 0; i < messageMax; i++)
	{
		eventViewer.push_back(eventMessage[i] = new EventMessage());
	}

	eventViewer.push_back(sealStockViewer = new SealItemStockViewer());
	eventViewer.push_back(eventTelop = new EventTelop());
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
EventViewer::~EventViewer()
{
	//�����������
	for (unsigned int i = 0; i < eventViewer.size(); i++)
	{
		SAFE_DELETE(eventViewer[i]);
	}

	//�C���X�^���X����ꂽ�z����N���A
	eventViewer.clear();
}

//=============================================================================
// �X�V����
//=============================================================================
void EventViewer::Update()
{
	for (unsigned int i = 0; i < eventViewer.size(); i++)
	{
		eventViewer[i]->Update();
	}

	PlayMessage();

#ifdef _DEBUG

	if (Keyboard::GetTrigger(DIK_M))
	{
		SetEventMessage("�C�x���g�����I");
	}

	if (Keyboard::GetTrigger(DIK_T))
	{
		SetEventTelop(eventTelop->Singularity, nullptr);
	}

	//if (Keyboard::GetTrigger(DIK_Y))
	//{
	//	SetEventTelop(eventTelop->AI_Strike, nullptr);
	//}

	//if (Keyboard::GetTrigger(DIK_1))
	//{
	//	sealStockViewer->parameterBox = true;
	//}

	//if (Keyboard::GetTrigger(DIK_2))
	//{
	//	sealStockViewer->parameterBox = false;
	//}

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

	for (unsigned int i = 0; i < eventViewer.size(); i++)
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
	//���b�Z�[�W�J�E���^�[��0����messageMex�܂łŃ��b�v�A���E���h
	Math::WrapAround(0, messageMax, messageSetCnt);

	if (messageSetCnt != 0)
	{
		//�ЂƂO�̃��b�Z�[�W���Đ��I�����Ă��Ȃ�J�E���g���Z�b�g
		if (!eventMessage[messageSetCnt - 1]->isPlaying)
		{
			messageSetCnt = 0;
		}
	}

	//�Z�b�g�J�E���g���J�E���g�A�b�v
	messageSetCnt++;
}

//=============================================================================
// ���b�Z�[�W�Đ�
//=============================================================================
void EventViewer::PlayMessage(void)
{
	//���b�Z�[�W���Ȃ������烊�^�[��
	if (messageContainer.empty()) return;

	//�Ō�̃��b�Z�[�W���v���C���Ȃ�I���܂Ń��^�[��
	if (eventMessage[messageMax - 1]->isPlaying) return;

	//���b�Z�[�W���J�E���g
	CountMessage();

	//�C�x���g���b�Z�[�W���Z�b�g
	eventMessage[messageSetCnt - 1]->SetEventMessage(messageContainer[0], messageSetCnt);

	//���b�Z�[�W�R���e�i�̐擪���폜
	messageContainer.erase(messageContainer.begin());
}

//=============================================================================
// �C�x���g�������b�Z�[�W��ݒu
//=============================================================================
void EventViewer::SetEventMessage(const std::string message)
{
	// �C�x���g���b�Z�[�W���Ȃ�
	if (message.empty()) return;

	//���b�Z�[�W���R���e�i�̖����ɒǉ�
	messageContainer.push_back(message);
}

//=============================================================================
// �C�x���g�����e���b�v��ݒu
//=============================================================================
void EventViewer::SetEventTelop(EventTelop::TelopID id, std::function<void(void)> Callback)
{
	eventTelop->Set(id, Callback);
}

//=============================================================================
// �p�����[�^�󂯎�菈��
//=============================================================================
void EventViewer::ReceiveParam(EventViewerParam &param)
{
	sealStockViewer->parameterBox = param.isStockSealed;
}
