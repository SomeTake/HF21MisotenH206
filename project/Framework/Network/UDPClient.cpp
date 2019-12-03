//=============================================================================
//
// UDP�N���C�A���g�N���X [UDPClient.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "UDPClient.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
HANDLE UDPClient::Thread = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPClient::UDPClient()
{
	Text = new TextureDrawer(D3DXVECTOR2(450.0f, 150.0f), 1, 2);
	Text->LoadTexture("data/TEXTURE/Viewer/ResultViewer/NetworkText.png");
	//Text->LoadTexture("data/TEXTURE/Viewer/ResultViewer/Text.png");
	Text->SetPosition(D3DXVECTOR3(1600.0f, 100.0f, 0.0f));

	// WinSock������
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// �\�P�b�g����
	ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// ���M��A�h���X
	ServerAddress.sin_port = htons(ServerPort);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = inet_addr("255.255.255.255");//�u���[�h�L���X�g�A�h���X

	// �u���[�h�L���X�g����
	int value = 1;
	setsockopt(ClientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&value, sizeof(value));

	// �N���C�A���g��M�X���b�h�J�n
	Thread = (HANDLE)_beginthreadex(NULL, 0, ThreadEntryPoint, this, 0, NULL);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPClient::~UDPClient()
{
	ThreadStop = true;

	// WinSock�I������
	closesocket(ClientSocket);
	WSACleanup();

	// ===============================================================
	// ���ӁB������ƃX���b�h�I���֐�(_endthreadex)���Ă΂Ȃ���
	// ���C���X���b�h���I��������ɑ��̃X���b�h�͂��̂܂܎��s���܂�
	// ��O�X���[�̉\��������
	// ===============================================================
	// �X���b�h���������܂ő҂�
	DWORD ThreadResult = WaitForSingleObject(Thread, INFINITE);
	if (ThreadResult == WAIT_OBJECT_0)
	{
		// �X���b�h�I��
		CloseHandle(Thread);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UDPClient::Update(void)
{
	Text->Update();

	//if (!InMultiThread)
	//	return;

	//DWORD Result = WaitForSingleObject(Thread, 0);
	//// �X���b�h����I��
	//if (Result == WAIT_OBJECT_0)
	//{
	//	Thread = 0;
	//	InMultiThread = false;
	//	TimeoutCount = 0;
	//}
	//// �^�C���A�E�g
	//else if (Result == WAIT_TIMEOUT)
	//{
	//	TimeoutCount++;
	//	// 10�񃊃N�G�X�g�A�������Ȃ�������X�V�I��
	//	RetryGetLastScore();
	//	if (TimeoutCount >= 10)
	//	{
	//		InMultiThread = false;
	//		TimeoutCount = 0;
	//	}
	//}
}

void UDPClient::Draw(void)
{
	if (!InLoading)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	Text->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// �����L���O�ǉ��p�P�b�g���M
//=============================================================================
void UDPClient::SendRankPacket(string NameStr, string AILevel)
{
	string Message;

	// ���̓��b�Z�[�W����
	Message = PacketHeader + "," + std::to_string(Packet::InsertRank) + "," + NameStr + "," + AILevel;

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// �����L���O�ǉ��p�P�b�g���M
//=============================================================================
void UDPClient::SendRankPacket(int NameInt, unsigned long long AILevel)
{
	string NameStr = std::to_string(NameInt);
	string AILevelStr = std::to_string(AILevel);
	SendRankPacket(NameStr, AILevelStr);
}

//=============================================================================
// �C�x���g���p�p�P�b�g���M
//=============================================================================
void UDPClient::SendEventPacket(string EventNo, string FieldLevel)
{
	string Message;

	// ���̓��b�Z�[�W����
	Message = PacketHeader + "," + std::to_string(Packet::EventLive) + "," + EventNo + "," + FieldLevel;

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// �C�x���g���p�p�P�b�g���M
//=============================================================================
void UDPClient::SendEventPacket(EventConfig::EventType EventNo, int FieldLevel)
{
	string EventNoStr = std::to_string(EventNo);
	string FieldLevelStr = std::to_string(FieldLevel);
	SendRankPacket(EventNoStr, FieldLevelStr);
}

//=============================================================================
// �t�B�[���h���x���A�b�v�p�P�b�g���M
//=============================================================================
void UDPClient::SendLevelUpPacket(void)
{
	string Message;

	// ���̓��b�Z�[�W����
	Message = PacketHeader + "," + std::to_string(Packet::LevelUp);

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// �Z�J���h�X���b�h
//=============================================================================
unsigned __stdcall UDPClient::ThreadEntryPoint(void* This)
{
	UDPClient* Temp = (UDPClient*)This;
	//Temp->InMultiThread = true;
	Temp->GetScorePacket();					// �{���̃Z�J���h�X���b�h�̏����֐�
	_endthreadex(0);					// �X���b�h�̎��s��~
	return 0;
}

//=============================================================================
// �T�[�o�[���烉���L���O�ŉ��ʂ̃X�R�A���擾
//=============================================================================
void UDPClient::GetScorePacket(void)
{
	// �f�[�^���M
	char data[256];
	string Message;
	int AddressLength;

	AddressLength = sizeof(ServerAddress);

	while (!ThreadStop)
	{
		memset(data, 0, sizeof(data));

		// ���b�Z�[�W��M
		recvfrom(ClientSocket, (char*)data, sizeof(data), 0, (sockaddr*)&ServerAddress, &AddressLength);

		// �f�[�^����
		Message = data;
		if (!Message.empty())
		{
			LastScore = std::stoull(Message);
			ReceiveSuccess = true;
			//ThreadCount = SuspendThread(Thread);
		}
		//else
		//{
		//	break;
		//}
	}
}

//=============================================================================
// �Z�J���h�X���b�h
//=============================================================================
void UDPClient::RetryGetLastScore(void)
{
	// �f�[�^���M
	string Message;
	int AddressLength;
	//InMultiThread = true;

	AddressLength = sizeof(ServerAddress);

	// ���̓��b�Z�[�W����
	Message = PacketHeader + "," + std::to_string(Packet::GetLastScore);

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, AddressLength);
}

unsigned long long UDPClient::GetLastScore(void)
{
	ReceiveSuccess = false;
	TimeoutCount = 0;
	InLoading = true;
	Text->SetAlpha(1.0f);

	// �X���b�h�܂��������Ȃ��̂ŁA������x�T�[�o�[�Ƀ��N�G�X�g
	RetryGetLastScore();

	while (TimeoutCount <= 60)
	{
		DWORD Result = WaitForSingleObject(Thread, 1);

		// �X���b�h����I��
		if (ReceiveSuccess)
		{
			break;
		}
		// �^�C���A�E�g
		else
		{
			TimeoutCount++;

			// ���N�G�X�g
			if (TimeoutCount % 3 == 0)
				RetryGetLastScore();
		}
	}

	if (ReceiveSuccess)
	{
		// ����
		Text->SetIndex(0);
		Text->Fade(60.0f, 0.0f, [&]()
		{
			InLoading = false;
		});
		return LastScore;
	}
	else
	{
		// ���s
		Text->SetIndex(1);
		Text->Fade(60.0f, 0.0f, [&]()
		{
			InLoading = false;
		});
		return 0;
	}
}
