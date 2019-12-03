//=============================================================================
//
// UDP�N���C�A���g�N���X [UDPClient.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _UDPClient_H_
#define _UDPClient_H_

#include <string>
#include "PacketConfig.h"
#include "../../source/Event/EventConfig.h"
#include "../../source/Viewer/Framework/ViewerDrawer/TextureDrawer.h"

using std::string;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPClient
{
private:
	static SOCKET ClientSocket;
	static sockaddr_in ServerAddress;
	TextureDrawer* Text;
	int TimeoutCount = 0;
	bool InLoading = false;
	bool ReceiveSuccess = false;
	bool ThreadStop = false;
	unsigned long long LastScore = 0;

	void TryGetLastScore(void);
	void GetScorePacket(void);

	// �}���`�X���b�h�p	
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);

public:
	UDPClient();
	~UDPClient();
	void Update(void);
	void Draw(void);
	static void SendRankPacket(string NameStr, string AILevel);
	static void SendRankPacket(int NameInt, unsigned long long AILevel);
	static void SendEventPacket(string EventNo, string FieldLevel);
	static void SendEventPacket(int EventNo, int FieldLevel);
	static void SendLevelUpPacket(void);
	unsigned long long GetLastScore(void);
};

#endif
