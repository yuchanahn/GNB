#pragma once

#include "CoreMinimal.h"


#include <thread>
#include <string>


auto CastUVec3 = [](auto v) { 
	FVector r;
	r.X = v.x;
	r.Y = v.y;
	r.Z = v.z;
	return  r;
};
auto CastVec3 = [](auto u) {
	return vec3d_t{
		u.X, u.Y, u.Z
	};
};


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
	void SendMouseInput(struct FMouseInput in);
};
