#pragma once

#include "CoreMinimal.h"


#include <thread>
#include <string>

class GNB_API TCPClient
{
	unsigned char buf[1024];

	class yc_client* clnt;
	std::thread* th;
	class AGNBGameModeBase* game_mode;
public:
	void Init(class AGNBGameModeBase* gm) { game_mode = gm; };
	TCPClient();
	~TCPClient();

	void ConnectServer(std::string ip, int port);
	void SendChatting(std::wstring msg);
	void GachaStart(char cnt);
};
